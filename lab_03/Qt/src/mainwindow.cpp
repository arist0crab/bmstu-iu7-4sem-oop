#include "mainwindow.hpp"

#include "LoadCommand.hpp"
#include "ObjectCommand.hpp"
#include "SceneCommand.hpp"
#include "CameraCommand.hpp"
#include "DefaultCamera.hpp"
#include "ManagerSolution.hpp"
#include "CameraManager.hpp"
#include "QtDrawer.hpp"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    auto scene = std::make_shared<QGraphicsScene>();
    ui->graphicsView->setScene(scene.get());
    
    auto drawer = std::make_shared<QtDrawer>(scene);
    auto drawManager = ManagerSolution::getManager<DrawManager>();
    drawManager->setDrawer(drawer);
    
    auto initCmd = std::make_shared<InitSceneCommand>();
    m_facade.execute(initCmd);
}

MainWindow::~MainWindow() 
{ 
	delete ui; 
}

void MainWindow::on_setCenterButton_clicked()
{
	bool ok;
	double cx = ui->setCenterXInput->text().toDouble(&ok);
	if (!ok) return;
	double cy = ui->setCenterYInput->text().toDouble(&ok);
	if (!ok) return;
	double cz = ui->setCenterZInput->text().toDouble(&ok);
	if (!ok) return;

    // TODO
	// getSelectedObjects();
	// for (auto id : m_selected)
	// {
	// 	auto cmd = std::make_shared<SetCenterCommand>(id, Vertex(cx, cy, cz));
	// 	m_facade.execute(cmd);
	// }

	drawScene();
}

void MainWindow::on_moveFigureButton_clicked()
{
	bool ok;
	double dx = ui->moveFigureXInput->text().toDouble(&ok);
	if (!ok) return;
	double dy = ui->moveFigureYInput->text().toDouble(&ok);
	if (!ok) return;
	double dz = ui->moveFigureZInput->text().toDouble(&ok);
	if (!ok) return;

	getSelectedObjects();
	for (auto id : m_selected)
	{
		auto cmd = std::make_shared<MoveObjectCommand>(id, dx, dy, dz);
		m_facade.execute(cmd);
	}

	drawScene();
}

void MainWindow::on_scaleFigureButton_clicked()
{
	bool ok;
	double kx = ui->scaleFigureXInput->text().toDouble(&ok);
	if (!ok) return;
	double ky = ui->scaleFigureYInput->text().toDouble(&ok);
	if (!ok) return;
	double kz = ui->scaleFigureZInput->text().toDouble(&ok);
	if (!ok) return;

	getSelectedObjects();
	for (auto id : m_selected)
	{
		auto cmd = std::make_shared<ScaleObjectCommand>(id, kx, ky, kz);
		m_facade.execute(cmd);
	}

	drawScene();
}

void MainWindow::on_rotateFigureButton_clicked()
{
	bool ok;
	double ax = ui->rotateFigureXInput->text().toDouble(&ok);
	if (!ok) return;
	double ay = ui->rotateFigureYInput->text().toDouble(&ok);
	if (!ok) return;
	double az = ui->rotateFigureZInput->text().toDouble(&ok);
	if (!ok) return;

	getSelectedObjects();
	for (auto id : m_selected)
	{
		auto cmd = std::make_shared<RotateObjectCommand>(id, ax, ay, az);
		m_facade.execute(cmd);
	}

	drawScene();
}

void MainWindow::on_loadFigureButton_clicked()
{
	QString filename = QFileDialog::getOpenFileName(this, "Открыть файл", "", "Текстовые файлы (*.txt);;OBJ файлы (*.obj)");
	if (filename.isEmpty())
		return;

	if (ui->listModelMode->isChecked())
	{
		auto cmd = std::make_shared<LoadListModelCommand>(filename.toStdString());
		m_facade.execute(cmd);
	}
	else
	{
		auto cmd = std::make_shared<LoadMatrixModelCommand>(filename.toStdString());
		m_facade.execute(cmd);
	}

	// TODO вынести эту порнографию
	auto sceneManager = ManagerSolution::getManager<SceneManager>();
	auto objects = sceneManager->getObjects();
	size_t lastId = objects.size() - 1;
	auto model = sceneManager->getObject(lastId);
	Vertex center = model->getCenter();

	ui->objectTable->insertRow(ui->objectTable->rowCount());
	ui->objectTable->setItem(ui->objectTable->rowCount() - 1, 0, 
		new QTableWidgetItem(QString::number(lastId)));
	ui->objectTable->setItem(ui->objectTable->rowCount() - 1, 1, 
		new QTableWidgetItem(QFileInfo(filename).fileName()));
	ui->objectTable->setItem(ui->objectTable->rowCount() - 1, 2, 
		new QTableWidgetItem(QString("(%1, %2, %3)").arg(center.X()).arg(center.Y()).arg(center.Z())));
	ui->objectTable->setItem(ui->objectTable->rowCount() - 1, 3, 
		new QTableWidgetItem("Модель"));

	drawScene();
}

void MainWindow::on_loadCameraButton_clicked()
{
	auto cmd = std::make_shared<AddCameraCommand>();
	m_facade.execute(cmd);
}

void MainWindow::on_deleteObjectButton_clicked()
{
	getSelectedObjects();
	for (auto id : m_selected)
	{
		auto cmd = std::make_shared<RemoveObjectCommand>(id);
		m_facade.execute(cmd);
	}

	drawScene();
}

void MainWindow::drawScene()
{
	auto cmd = std::make_shared<DrawSceneCommand>();
	m_facade.execute(cmd);
}

void MainWindow::getSelectedObjects()
{
	m_selected.clear();
	auto selected = ui->objectTable->selectedItems();
	for (auto item : selected)
		if (item->column() == 0)
			m_selected.push_back(item->row());
}