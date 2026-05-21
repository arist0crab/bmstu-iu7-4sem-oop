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
#include <algorithm>


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
        if (!sceneManager->getObjects().empty())
        {
            size_t startCameraId = 0;
            if (auto camera = sceneManager->getObject(startCameraId))
            {
                insertRow(startCameraId, "Камера " + std::to_string(startCameraId), camera->getCenter(), "Камера");
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
    ManagerSolution::getManager<DrawManager>()->setDrawer(drawer);
}

// ===============================
//          Трансформации
// ===============================

void MainWindow::processObjectsTransformation(const std::function<std::shared_ptr<BaseCommand>(size_t)>& commandFactory)
{
    getSelectedObjects();
    if (m_selected.empty()) return;

    try
    {
        for (const auto id : m_selected)
        {
            auto cmd = commandFactory(id);
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

void MainWindow::on_setCenterButton_clicked()
{
    bool ok;
    double cx = ui->setCenterXInput->text().toDouble(&ok); if (!ok) return;
    double cy = ui->setCenterYInput->text().toDouble(&ok); if (!ok) return;
    double cz = ui->setCenterZInput->text().toDouble(&ok); if (!ok) return;

    processObjectsTransformation([=](size_t id) {
        return std::make_shared<SetCenterCommand>(id, Vertex(cx, cy, cz));
    });
}

void MainWindow::on_moveFigureButton_clicked()
{
    bool ok;
    double dx = ui->moveFigureXInput->text().toDouble(&ok); if (!ok) return;
    double dy = ui->moveFigureYInput->text().toDouble(&ok); if (!ok) return;
    double dz = ui->moveFigureZInput->text().toDouble(&ok); if (!ok) return;

    processObjectsTransformation([=](size_t id) {
        return std::make_shared<MoveObjectCommand>(id, dx, dy, dz);
    });
}

void MainWindow::on_scaleFigureButton_clicked()
{
    bool ok;
    double kx = ui->scaleFigureXInput->text().toDouble(&ok); if (!ok) return;
    double ky = ui->scaleFigureYInput->text().toDouble(&ok); if (!ok) return;
    double kz = ui->scaleFigureZInput->text().toDouble(&ok); if (!ok) return;

    if (kx == 0 || ky == 0 || kz == 0)
    {
        QMessageBox::warning(this, "Внимание", "Коэффициент масштабирования не может быть равен 0.");
        return;
    }

    processObjectsTransformation([=](size_t id) {
        return std::make_shared<ScaleObjectCommand>(id, kx, ky, kz);
    });
}

void MainWindow::on_rotateFigureButton_clicked()
{
    bool ok;
    double ax = ui->rotateFigureXInput->text().toDouble(&ok); if (!ok) return;
    double ay = ui->rotateFigureYInput->text().toDouble(&ok); if (!ok) return;
    double az = ui->rotateFigureZInput->text().toDouble(&ok); if (!ok) return;

    ax = qDegreesToRadians(ax);
    ay = qDegreesToRadians(ay);
    az = qDegreesToRadians(az);

    processObjectsTransformation([=](size_t id) {
        return std::make_shared<RotateObjectCommand>(id, ax, ay, az);
    });
}

// ===============================
//       Загрузка и удаление
// ===============================

void MainWindow::on_loadFigureButton_clicked()
{
    QString qFilename = QFileDialog::getOpenFileName(this, "Открыть файл", "", "Текстовые файлы (*.txt);;OBJ файлы (*.obj)");
    if (qFilename.isEmpty()) return;

    try
    {
        std::shared_ptr<BaseCommand> cmd;
        if (ui->listModelMode->isChecked())
            cmd = std::make_shared<LoadListModelCommand>(qFilename.toStdString());
        else
            cmd = std::make_shared<LoadMatrixModelCommand>(qFilename.toStdString());

        m_facade.execute(cmd);
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
        std::shared_ptr<BaseCommand> cmd = std::make_shared<AddDefaultCameraCommand>();
        m_facade.execute(cmd);

        auto sceneManager = ManagerSolution::getManager<SceneManager>();
        size_t lastId = sceneManager->getObjects().size() - 1;
        
        if (auto camera = sceneManager->getObject(lastId))
            insertRow(lastId, "Камера " + std::to_string(lastId), camera->getCenter(), "Камера");

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

void MainWindow::on_deleteObjectButton_clicked()
{
    getSelectedObjects();
    if (m_selected.empty()) return;

    std::sort(m_selected.begin(), m_selected.end(), std::greater<size_t>());

    if (countSelectedCameras() >= countTotalCameras() && countSelectedCameras() > 0)
    {
        QMessageBox::warning(this, "Предупреждение", "Невозможно удалить последнюю камеру. На сцене должен оставаться как минимум один источник обзора.");
        return;
    }

    try
    {
        removeSelectedObjects();
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
    if (ui->objectTable->item(id, 3)->text() != "Камера")
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
//    Декомпозированные хелперы
// ===============================

size_t MainWindow::countTotalCameras() const
{
    size_t total = 0;
    for (int row = 0; row < ui->objectTable->rowCount(); ++row)
        if (auto item = ui->objectTable->item(row, 3); item && item->text() == "Камера")
            total++;

    return total;
}

size_t MainWindow::countSelectedCameras() const
{
    size_t selectedCount = 0;
    for (const auto id : m_selected)
        if (auto item = ui->objectTable->item(id, 3); item && item->text() == "Камера")
            selectedCount++;

    return selectedCount;
}

void MainWindow::removeSelectedObjects()
{
    auto cameraManager = ManagerSolution::getManager<CameraManager>();

    for (const auto id : m_selected)
    {
        if (auto item = ui->objectTable->item(id, 3); item && item->text() == "Камера")
            cameraManager->removeCamera(id);

        std::shared_ptr<BaseCommand> cmd = std::make_shared<RemoveObjectCommand>(id);
        m_facade.execute(cmd);

        ui->objectTable->removeRow(id);
    }

    for (int i = 0; i < ui->objectTable->rowCount(); ++i)
        ui->objectTable->item(i, 0)->setText(QString::number(i));

    m_selected.clear();
    updateActiveCameraHighlight(cameraManager->getActiveCameraId());
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
        if (el->column() == 0)
            m_selected.push_back(el->row());
}

void MainWindow::addModelToTable(const QString &filename)
{
    auto sceneManager = ManagerSolution::getManager<SceneManager>();
    size_t lastId = sceneManager->getObjects().size() - 1;
    
    if (auto model = sceneManager->getObject(lastId))
        insertRow(lastId, QFileInfo(filename).fileName().toStdString(), model->getCenter(), "Модель");
}

void MainWindow::insertRow(size_t id, const std::string &name, const Vertex &center, const std::string &type)
{
    int targetRow = ui->objectTable->rowCount();
    ui->objectTable->insertRow(targetRow);
    
    QString centerStr = QString("(%1; %2; %3)").arg(center.X()).arg(center.Y()).arg(center.Z());

    ui->objectTable->setItem(targetRow, 0, new QTableWidgetItem(QString::number(id)));
    ui->objectTable->setItem(targetRow, 1, new QTableWidgetItem(QString(name.c_str())));
    ui->objectTable->setItem(targetRow, 2, new QTableWidgetItem(centerStr));
    ui->objectTable->setItem(targetRow, 3, new QTableWidgetItem(QString(type.c_str())));
}

void MainWindow::updateActiveCameraHighlight(size_t activeId)
{
    const QColor defaultTextColor = QColor(226, 194, 155); 
    const QColor activeCameraColor = QColor(255, 130, 45); 

    for (int row = 0; row < ui->objectTable->rowCount(); ++row)
    {
        auto typeItem = ui->objectTable->item(row, 3);
        if (!typeItem || typeItem->text() != "Камера") continue;

        bool ok;
        size_t currentId = ui->objectTable->item(row, 0)->text().toULongLong(&ok);
        if (!ok) continue;
        
        bool isActive = (currentId == activeId);
        QColor targetColor = isActive ? activeCameraColor : defaultTextColor;

        if (auto nameItem = ui->objectTable->item(row, 1))
            nameItem->setText(QString::fromStdString("Камера " + std::to_string(currentId)));

        for (int col = 0; col < ui->objectTable->columnCount(); ++col)
            if (auto item = ui->objectTable->item(row, col))
                item->setForeground(targetColor);
    }
}