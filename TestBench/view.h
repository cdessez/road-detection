#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QDir>
#include <QSettings>

#include "imageprocessing.h"

namespace Ui {
    class View;
}

class View : public QMainWindow
{
    Q_OBJECT

public:
    explicit View();
    ~View();

public slots:
    void updateResults() ;

protected:

private slots:
    void on_chargerButton_clicked() ;
    void showSample() ;
    void on_processButton_clicked() ;
    void on_enregistrerButton_clicked() ;
    void on_checkA_toggled(bool b) ;
    void on_checkB_toggled(bool b) ;
    void on_checkC_toggled(bool b) ;
    void on_checkD_toggled(bool b) ;
    void on_checkE_toggled(bool b) ;
    void on_checkF_toggled(bool b) ;
    void on_checkG_toggled(bool b) ;
    void on_checkH_toggled(bool b) ;
    void on_checkI_toggled(bool b) ;
    void on_saveSettings_clicked() ;
    void on_medianFilterA_toggled(bool b) ;
    void on_lowPassFilterA_toggled(bool b) ;
    void on_filterSizeA_valueChanged(int i) ;
    void on_graySpaceB_toggled(bool b) ;
    void on_bgrSpaceB_toggled(bool b) ;
    void on_cieSpaceB_toggled(bool b) ;
    void on_hsvSpaceB_toggled(bool b) ;
    void on_ycrcbSpaceB_toggled(bool b) ;
    void on_backprojectingB_toggled(bool b) ;
    void on_backprojectingTresholdB_valueChanged(int i) ;
    void on_distanceFilterB_toggled(bool b) ;
    void on_distanceFilterTresholdB_valueChanged(int i) ;
    void on_samplePosxB_valueChanged(int i) ;
    void on_samplePosyB_valueChanged(int i) ;
    void on_sampleSizeB_valueChanged(int i) ;
    void on_medianFilterC_toggled(bool b) ;
    void on_filterSizeC_valueChanged(int i) ;
    void on_openningC_toggled(bool b) ;
    void on_closingC_toggled(bool b) ;
    void on_closingPrioritaryC_toggled(bool b) ;
    void on_closingSizeC_valueChanged(int i) ;
    void on_openningSizeC_valueChanged(int i) ;
    void on_closingRepetitionsC_valueChanged(int i) ;
    void on_openningRepetitionsC_valueChanged(int i) ;
    void on_findContoursD_toggled(bool b) ;
    void on_doMinPerimeterD_toggled(bool b) ;
    void on_cannyD_toggled(bool b) ;
    void on_minPerimeterD_valueChanged(int i) ;
    void on_thicknessD_valueChanged(int i) ;
    void on_cannyLowThresholdD_valueChanged(int i) ;
    void on_cannyHighThresholdD_valueChanged(int i) ;
    void on_stepRadiiE_valueChanged(int i) ;
    void on_stepAngleE_valueChanged(int i) ;
    void on_thresholdE_valueChanged(int i) ;
    void on_miniRoadAngleE_valueChanged(int i) ;
    void on_fourPointsRatioF_valueChanged(double d) ;
    void on_resultSizeRatioF_valueChanged(double d) ;
    void on_resolutionRatioF_valueChanged(int i) ;
    void on_aG_valueChanged(double d) ;
    void on_bG_valueChanged(double d) ;
    void on_averageBlurG_toggled(bool b) ;
    void on_blurSizeG_valueChanged(int i) ;
    void on_shiftingRigidityH_valueChanged(int i) ;
    void on_widthRigidityH_valueChanged(int i) ;
    void on_maxWidthDifferenceH_valueChanged(int i) ;
    void on_cutColorH_toggled(bool b) ;
    void on_cuttingLimitH_valueChanged(int i) ;
    void on_transparencyH_valueChanged(int i) ;


private:
    Ui::View *ui;
    ImageProcessing imageProcessing ;
    bool imageLoaded ;
    int colorSpaceB ;
    QSettings* settings ;
};

#endif // VIEW_H
