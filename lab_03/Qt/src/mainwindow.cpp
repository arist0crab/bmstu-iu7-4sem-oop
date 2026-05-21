#include "mainwindow.hpp"
#include "LoadCommand.hpp"
#include "ObjectCommand.hpp"
#include "SceneCommand.hpp"
#include "CameraCommand.hpp"
#include "ManagerSolution.hpp"
#include "DrawManager.hpp"
#include "SceneManager.hpp"
#include "CameraManager.hpp"
#include "QtDrawer.hpp"
#include "BaseException.hpp"

#include <QFileDialog>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->objectTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->objectTable->setFocusPolicy(Qt::NoFocus);
    ui->objectTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->objectTable->setContextMenuPolicy(Qt::CustomContextMenu);

    createScene(ui->graphicsView);

    try
    {
        std::shared_ptr<BaseCommand> initCmd = std::make_shared<InitSceneCommand>();
        m_facade.execute(initCmd);

        auto sceneManager = ManagerSolution::getManager<SceneManager>();
        auto objects = sceneManager->getObjects();
        
        // TODO декомпозировать
        if (!objects.empty())
        {
            size_t firstId = 0;
            auto camera = sceneManager->getObject(firstId);
            
            if (camera)
            {
                Vertex center = camera->getCenter();
                insertRow(firstId, "Камера " + std::to_string(firstId), center, "Камера");
            }
        }

        updateActiveCameraHighlight(0);
        drawScene();
    }
    catch (const BaseException &ex)
    {
        QMessageBox::critical(this, "Error!", ex.what());
    }
    catch (const std::exception &ex)
    {
        QMessageBox::critical(this, "Unknown error!", ex.what());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ===============================
//        Инициализация сцены
// ===============================

void MainWindow::createScene(QWidget *parent)
{
    const int w = ui->graphicsView->width();
    const int h = ui->graphicsView->height();

    auto scene = std::shared_ptr<QGraphicsScene>(new QGraphicsScene{0, 0, (qreal)w, (qreal)h, parent}, [](QGraphicsScene *) {});
    scene->setSceneRect(QRect{0, 0, w, h});
    scene->setBackgroundBrush(QColor::fromRgb(20, 42, 69));

    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setScene(scene.get());

    auto drawer = std::make_shared<QtDrawer>(scene);
    auto drawManager = ManagerSolution::getManager<DrawManager>();
    drawManager->setDrawer(drawer);
}

// ===============================
//          Трансформации
// ===============================

void MainWindow::on_setCenterButton_clicked()
{
    double cx, cy, cz;
    bool ok;

    cx = ui->setCenterXInput->text().toDouble(&ok);
    if (!ok) return;
    cy = ui->setCenterYInput->text().toDouble(&ok);
    if (!ok) return;
    cz = ui->setCenterZInput->text().toDouble(&ok);
    if (!ok) return;

    getSelectedObjects();
    Vertex newCenter;

    try
    {
        for (const auto id : m_selected)
        {
            std::shared_ptr<BaseCommand> cmd = std::make_shared<SetCenterCommand>(id, Vertex(cx, cy, cz));
            m_facade.execute(cmd);
        }

        drawScene();
    }
    catch (const BaseException &ex)
    {
        QMessageBox::critical(this, "Error!", ex.what());
    }
    catch (const std::exception &ex)
    {
        QMessageBox::critical(this, "Unknown error!", ex.what());
    }
}

void MainWindow::on_moveFigureButton_clicked()
{
    double dx, dy, dz;
    bool ok;

    dx = ui->moveFigureXInput->text().toDouble(&ok);
    if (!ok) return;
    dy = ui->moveFigureYInput->text().toDouble(&ok);
    if (!ok) return;
    dz = ui->moveFigureZInput->text().toDouble(&ok);
    if (!ok) return;

    getSelectedObjects();

    try
    {
        for (const auto id : m_selected)
        {
            std::shared_ptr<BaseCommand> cmd = std::make_shared<MoveObjectCommand>(id, dx, dy, dz);
            m_facade.execute(cmd);
        }

        drawScene();
    }
    catch (const BaseException &ex)
    {
        QMessageBox::critical(this, "Error!", ex.what());
    }
    catch (const std::exception &ex)
    {
        QMessageBox::critical(this, "Unknown error!", ex.what());
    }
}

void MainWindow::on_scaleFigureButton_clicked()
{
    double kx, ky, kz;
    bool ok;

    kx = ui->scaleFigureXInput->text().toDouble(&ok);
    if (!ok) return;
    ky = ui->scaleFigureYInput->text().toDouble(&ok);
    if (!ok) return;
    kz = ui->scaleFigureZInput->text().toDouble(&ok);
    if (!ok) return;

    if (kx == 0 || ky == 0 || kz == 0)
    {
        QMessageBox::warning(this, "Внимание", "Коэффициент масштабирования не может быть равен 0.");
        return;
    }

    getSelectedObjects();

    try
    {
        for (const auto id : m_selected)
        {
            std::shared_ptr<BaseCommand> cmd = std::make_shared<ScaleObjectCommand>(id, kx, ky, kz);
            m_facade.execute(cmd);
        }

        drawScene();
    }
    catch (const BaseException &ex)
    {
        QMessageBox::critical(this, "Error!", ex.what());
    }
    catch (const std::exception &ex)
    {
        QMessageBox::critical(this, "Unknown error!", ex.what());
    }
}

void MainWindow::on_rotateFigureButton_clicked()
{
    double ax, ay, az;
    bool ok;

    ax = ui->rotateFigureXInput->text().toDouble(&ok);
    if (!ok) return;
    ay = ui->rotateFigureYInput->text().toDouble(&ok);
    if (!ok) return;
    az = ui->rotateFigureZInput->text().toDouble(&ok);
    if (!ok) return;

    ax = qDegreesToRadians(ax);
    ay = qDegreesToRadians(ay);
    az = qDegreesToRadians(az);

    getSelectedObjects();

    try
    {
        for (const auto id : m_selected)
        {
            std::shared_ptr<BaseCommand> cmd = std::make_shared<RotateObjectCommand>(id, ax, ay, az);
            m_facade.execute(cmd);
        }

        drawScene();
    }
    catch (const BaseException &ex)
    {
        QMessageBox::critical(this, "Error!", ex.what());
    }
    catch (const std::exception &ex)
    {
        QMessageBox::critical(this, "Unknown error!", ex.what());
    }
}

// ===============================
//       Загрузка и удаление
// ===============================

void MainWindow::on_loadFigureButton_clicked()
{
    QString qFilename = QFileDialog::getOpenFileName(
        this, "Открыть файл", "", "Текстовые файлы (*.txt);;OBJ файлы (*.obj)");

    if (qFilename.isEmpty())
        return;

    std::string filename = qFilename.toStdString();

    try
    {
        if (ui->listModelMode->isChecked())
        {
            std::shared_ptr<BaseCommand> cmd = std::make_shared<LoadListModelCommand>(filename);
            m_facade.execute(cmd);
        }
        else
        {
            std::shared_ptr<BaseCommand> cmd = std::make_shared<LoadMatrixModelCommand>(filename);
            m_facade.execute(cmd);
        }

        addModelToTable(qFilename);
        drawScene();
    }
    catch (const BaseException &ex)
    {
        QMessageBox::critical(this, "Error!", ex.what());
    }
    catch (const std::exception &ex)
    {
        QMessageBox::critical(this, "Unknown error!", ex.what());
    }
}

void MainWindow::on_loadCameraButton_clicked()
{
    try
    {
        auto sceneManager = ManagerSolution::getManager<SceneManager>();
        size_t objectsBefore = sceneManager->getObjects().size();

        std::shared_ptr<BaseCommand> cmd = std::make_shared<AddDefaultCameraCommand>();
        m_facade.execute(cmd);

        auto objectsAfter = sceneManager->getObjects();
        size_t lastId = objectsAfter.size() - 1;
        auto camera = sceneManager->getObject(lastId);
        
        if (camera)
        {
            Vertex center = camera->getCenter();
            insertRow(lastId, "Камера " + std::to_string(lastId), center, "Камера");
        }

        updateActiveCameraHighlight(lastId);
        drawScene();
    }
    catch (const BaseException &ex)
    {
        QMessageBox::critical(this, "Error!", ex.what());
    }
    catch (const std::exception &ex)
    {
        QMessageBox::critical(this, "Unknown error!", ex.what());
    }
}

// TODO декомпозировать
void MainWindow::on_deleteObjectButton_clicked()
{
    getSelectedObjects();
    if (m_selected.empty()) return;

    try
    {
        std::sort(m_selected.begin(), m_selected.end(), std::greater<size_t>());
        
        auto cameraManager = ManagerSolution::getManager<CameraManager>();

        int totalCamerasInTable = 0;
        for (int row = 0; row < ui->objectTable->rowCount(); ++row)
        {
            auto typeItem = ui->objectTable->item(row, 3);
            if (typeItem && typeItem->text() == "Камера")
                totalCamerasInTable++;
        }

        int camerasToDelete = 0;
        for (const auto id : m_selected)
        {
            auto typeItem = ui->objectTable->item(id, 3);
            if (typeItem && typeItem->text() == "Камера")
                camerasToDelete++;
        }

        if (camerasToDelete > 0 && camerasToDelete >= totalCamerasInTable)
        {
            QMessageBox::warning(this, "Предупреждение", "Невозможно удалить последнюю камеру. На сцене должен оставаться как минимум один источник обзора.");
            return;
        }

        for (const auto id : m_selected)
        {
            auto typeItem = ui->objectTable->item(id, 3);
            if (typeItem && typeItem->text() == "Камера")
                cameraManager->removeCamera(id);

            std::shared_ptr<BaseCommand> cmd = std::make_shared<RemoveObjectCommand>(id);
            m_facade.execute(cmd);

            ui->objectTable->removeRow(id);
        }

        for (int i = 0; i < ui->objectTable->rowCount(); ++i)
            ui->objectTable->item(i, 0)->setText(QString::number(i));

        m_selected.clear();

        size_t activeCamId = cameraManager->getActiveCameraId();
        updateActiveCameraHighlight(activeCamId);

        drawScene();
    }
    catch (const BaseException &ex)
    {
        QMessageBox::critical(this, "Error!", ex.what());
    }
    catch (const std::exception &ex)
    {
        QMessageBox::critical(this, "Unknown error!", ex.what());
    }
}

void MainWindow::on_setActiveCameraButton_clicked()
{
    getSelectedObjects();
    if (m_selected.empty()) return;

    size_t id = m_selected[0];
    auto type = ui->objectTable->item(id, 3)->text();
    if (type != "Камера")
    {
        QMessageBox::warning(this, "Предупреждение", "Выбранный объект не является камерой.");
        return;
    }

    try
    {
        std::shared_ptr<BaseCommand> cmd = std::make_shared<SetActiveCameraCommand>(id);
        m_facade.execute(cmd);

        updateActiveCameraHighlight(id);
        drawScene(); 
    }
    catch (const BaseException &ex)
    {
        QMessageBox::critical(this, "Error!", ex.what());
    }
    catch (const std::exception &ex)
    {
        QMessageBox::critical(this, "Unknown error!", ex.what());
    }
}

// ===============================
//          Утилиты
// ===============================

void MainWindow::drawScene()
{
    std::shared_ptr<BaseCommand> cmd = std::make_shared<DrawSceneCommand>();
    m_facade.execute(cmd);
}

void MainWindow::getSelectedObjects()
{
    auto selected = ui->objectTable->selectedItems();

    m_selected.clear();

    for (const auto el : selected)
    {
        if (el->column() == 0)
            m_selected.push_back(el->row());
    }
}

void MainWindow::addModelToTable(const QString &filename)
{
    auto sceneManager = ManagerSolution::getManager<SceneManager>();
    auto objects = sceneManager->getObjects();
    size_t lastId = objects.size() - 1;
    auto model = sceneManager->getObject(lastId);
    Vertex center = model->getCenter();

    insertRow(lastId, QFileInfo(filename).fileName().toStdString(), center, "Модель");
}

void MainWindow::insertRow(size_t id, const std::string &name, const Vertex &center, const std::string &type)
{
    ui->objectTable->insertRow(ui->objectTable->rowCount());
    ui->objectTable->setItem(ui->objectTable->rowCount() - 1, 0, new QTableWidgetItem{QString::number(id)});
    ui->objectTable->setItem(ui->objectTable->rowCount() - 1, 1, new QTableWidgetItem{QString(name.c_str())});
    ui->objectTable->setItem(ui->objectTable->rowCount() - 1, 2,
                             new QTableWidgetItem{"(" + QString::number(center.X()) + "; "
                                                       + QString::number(center.Y()) + "; "
                                                       + QString::number(center.Z()) + ")"});
    ui->objectTable->setItem(ui->objectTable->rowCount() - 1, 3, new QTableWidgetItem{QString(type.c_str())});
}

void MainWindow::updateActiveCameraHighlight(size_t activeId)
{
    QColor defaultTextColor = QColor(226, 194, 155); 
    QColor activeCameraColor = QColor(255, 130, 45); 

    for (int row = 0; row < ui->objectTable->rowCount(); ++row)
    {
        auto typeItem = ui->objectTable->item(row, 3);
        if (typeItem && typeItem->text() == "Камера")
        {
            bool ok;
            size_t currentId = ui->objectTable->item(row, 0)->text().toULongLong(&ok);
            
            if (ok)
            {
                bool isActive = (currentId == activeId);
                
                std::string displayName = "Камера " + std::to_string(currentId);
                QColor targetColor = isActive ? activeCameraColor : defaultTextColor;

                if (auto nameItem = ui->objectTable->item(row, 1))
                    nameItem->setText(QString::fromStdString(displayName));

                for (int col = 0; col < ui->objectTable->columnCount(); ++col)
                    if (auto item = ui->objectTable->item(row, col))
                        item->setForeground(targetColor);
            }
        }
    }
}