//******************************************************************************
//include
//******************************************************************************
#include "main.h"
#include "ButtonFConditionTypes.h"
#include "ButtonFTimerTypes.h"
#include "cTimerButton.h"
#include "cConditionButton.h"
//******************************************************************************
// Variables
//******************************************************************************
//------------------------------------------------------------------------------
// Global
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local Variable
//------------------------------------------------------------------------------
QVector<cTimerButton> vTimerButton = QVector<cTimerButton>(10);
QVector<cConditionButton> vCondotoinButton = QVector<cConditionButton>(10);

//------------------------------------------------------------------------------
// Local Class
//------------------------------------------------------------------------------
MainWindow* window;
USBProcedure* USBProcess;
EmulationOrchestrator* buttonProcess;
SaveManager* saver;
//******************************************************************************
// Function prototype
//******************************************************************************
void CreateMainWindows(const QVector<cTimerButton>& vTButton,
    const QVector<cConditionButton>& vCButton);
void StartUSBProcedure(void);
void StartButtonProcedure(void);
void StartSaveProcedure(QVector<cTimerButton>& vTButton,
    QVector<cConditionButton>& vCButton);
//******************************************************************************
// Function
//******************************************************************************
int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

    StartSaveProcedure(vTimerButton, vCondotoinButton);
    StartUSBProcedure();
    StartButtonProcedure();    
    CreateMainWindows(vTimerButton, vCondotoinButton);

	return app.exec();
}
//------------------------------------------------------------------------------
void CreateMainWindows(const QVector<cTimerButton>& vTButton,
    const QVector<cConditionButton>& vCButton)
{
    window = new MainWindow(vTButton.size(), vCButton.size());
    
    //for (cTimerButton button : vTButton)
    for (int num = 0; num < vTButton.size(); ++num)
    {
        ButtonFTimer_DType button;

        button.activate = vTButton[num].getActive();
        button.ctrl = vTButton[num].getCtrl();
        button.alt = vTButton[num].getAlt();
        button.shift = vTButton[num].getShift();
        button.n_window = vTButton[num].getNWindow();
        button.button = vTButton[num].getIndexButton();
        button.period = vTButton[num].getPeriod();
        button.repeat = vTButton[num].getRepeat();
        button.pause = vTButton[num].getPause();

        window->SetGUITimerButton(num, button);
    }

    for (int num = 0; num < vCButton.size(); ++num)
    {
        ButtonFCondition_DType button;

        button.activate = vCButton[num].getActive();
        button.ctrl = vCButton[num].getCtrl();
        button.alt = vCButton[num].getAlt();
        button.shift = vCButton[num].getShift();
        button.n_window = vCButton[num].getNWindow();
        button.button = vCButton[num].getIndexButton();
        button.period = vCButton[num].getPeriod();
        button.repeat = vCButton[num].getRepeat();
        button.pause = vCButton[num].getPause();
        button.color_condition = vCButton[num].getCondition();
        button.color_set = vCButton[num].getColor();

        window->SetGUIConditionButton(num, button);
    }
    window->show();

    QObject::connect(USBProcess, &USBProcedure::GUISetStatusConection, 
        window, &MainWindow::handleStatusConnection);    
    QObject::connect(window, &MainWindow::elementTimerChanged, 
        buttonProcess, &EmulationOrchestrator::UpdateParametersButtonTimer, 
        Qt::DirectConnection);
    QObject::connect(window, &MainWindow::elementPixelChanged, 
        buttonProcess, &EmulationOrchestrator::UpdateParametersButtonCondition, 
        Qt::DirectConnection);
}
//------------------------------------------------------------------------------
void StartUSBProcedure(void)
{
    QThread* threadUSBProcess = new QThread;
    USBProcess = new USBProcedure();
    USBProcess->moveToThread(threadUSBProcess);
    QObject::connect(threadUSBProcess, &QThread::started, USBProcess, &USBProcedure::process);
    QObject::connect(USBProcess, &USBProcedure::finished, threadUSBProcess, &QThread::quit);
    QObject::connect(USBProcess, &USBProcedure::finished, USBProcess, &USBProcedure::deleteLater);
    QObject::connect(threadUSBProcess, &QThread::finished, threadUSBProcess, &QThread::deleteLater);
    threadUSBProcess->start();
}
//------------------------------------------------------------------------------
void StartButtonProcedure(void)
{
    QThread* threadButtonProcess = new QThread;
    buttonProcess = new EmulationOrchestrator(vTimerButton, vCondotoinButton);
    buttonProcess->moveToThread(threadButtonProcess);
    QObject::connect(threadButtonProcess, &QThread::started, buttonProcess, &EmulationOrchestrator::process);
    QObject::connect(buttonProcess, &EmulationOrchestrator::finished, threadButtonProcess, &QThread::quit);
    QObject::connect(buttonProcess, &EmulationOrchestrator::finished, buttonProcess, &EmulationOrchestrator::deleteLater);
    QObject::connect(threadButtonProcess, &QThread::finished, threadButtonProcess, &QThread::deleteLater);
    threadButtonProcess->start();

    QObject::connect(buttonProcess, &EmulationOrchestrator::SaveParametersButtonTimer,
        saver, &SaveManager::handleUpdateDefaultParamsFTimer);
    QObject::connect(buttonProcess, &EmulationOrchestrator::SaveParametersButtonCondition,
        saver, &SaveManager::handleUpdateDefaultParamsFCondition);
}
//------------------------------------------------------------------------------
void StartSaveProcedure(QVector<cTimerButton>& vTButton,
    QVector<cConditionButton>& vCButton)
{
    saver = new SaveManager();
    saver->DefaultLoadOptions(vTButton, vCButton);
}