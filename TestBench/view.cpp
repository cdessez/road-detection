#include "view.h"
#include "ui_view.h"
#include "imageprocessing.h"


View::View() :
    QMainWindow(), imageProcessing(),
    colorSpaceB(3), imageLoaded(false),
    ui(new Ui::View)
{
    ui->setupUi(this);
    QObject::connect(&imageProcessing, SIGNAL(finished()), this, SLOT(updateResults())) ;

    QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::applicationDirPath()) ;
    settings = new QSettings(QSettings::IniFormat, QSettings::UserScope, "testbench-settings", "testbench") ;
    if (settings->contains("doA")) ui->checkA->setChecked(settings->value("doA").toBool());
    if (settings->contains("doB")) ui->checkB->setChecked(settings->value("doB").toBool());
    if (settings->contains("doC")) ui->checkC->setChecked(settings->value("doC").toBool());
    if (settings->contains("doD")) ui->checkD->setChecked(settings->value("doD").toBool());
    if (settings->contains("doE")) ui->checkE->setChecked(settings->value("doE").toBool());
    if (settings->contains("doF")) ui->checkF->setChecked(settings->value("doF").toBool());
    if (settings->contains("doG")) ui->checkG->setChecked(settings->value("doG").toBool());
    if (settings->contains("doH")) ui->checkH->setChecked(settings->value("doH").toBool());
    if (settings->contains("doI")) ui->checkI->setChecked(settings->value("doI").toBool());

    if (settings->contains("doMedianFilterA")) ui->medianFilterA->setChecked(settings->value("doMedianFilterA").toBool());
    if (settings->contains("doLowPassFilterA")) ui->lowPassFilterA->setChecked(settings->value("doLowPassFilterA").toBool());
    if (settings->contains("filterSizeA")) ui->filterSizeA->setValue(settings->value("filterSizeA").toInt());

    if (settings->contains("colorSpaceB")) {
        switch (settings->value("colorSpaceB").toInt()){
        case 0 : ui->graySpaceB->setChecked(true); break ;
        case 1 : ui->bgrSpaceB->setChecked(true); break ;
        case 2 : ui->cieSpaceB->setChecked(true); break ;
        case 3 : ui->hsvSpaceB->setChecked(true); break ;
        case 4 : ui->ycrcbSpaceB->setChecked(true); break;
        }
    }
    if (settings->contains("doBackProjectingB")) ui->backprojectingB->setChecked(settings->value("doBackprojectingB").toBool());
    if (settings->contains("doDistanceFilterB")) ui->distanceFilterB->setChecked(settings->value("doDistanceFilterB").toBool());
    if (settings->contains("backprojectingTresholdB")) ui->backprojectingTresholdB->setValue(settings->value("backprojectingTresholdB").toInt());
    if (settings->contains("distanceFilterTresholdB")) ui->distanceFilterTresholdB->setValue(settings->value("distanceFilterTresholdB").toInt());
    if (settings->contains("samplePosxB")) ui->samplePosxB->setValue(settings->value("samplePosxB").toInt());
    if (settings->contains("samplePosyB")) ui->samplePosyB->setValue(settings->value("samplePosyB").toInt());
    if (settings->contains("sampleSizeB")) ui->sampleSizeB->setValue(settings->value("sampleSizeB").toInt());

    if (settings->contains("doMedianFilterC")) ui->medianFilterC->setChecked(settings->value("doMedianFilterC").toBool());
    if (settings->contains("doClosingC")) ui->closingC->setChecked(settings->value("doClosingC").toBool());
    if (settings->contains("doOpenningC")) ui->openningC->setChecked(settings->value("doOpenningC").toBool());
    if (settings->contains("closingPrioritaryC")) {
        ui->closingPrioritaryC->setChecked(settings->value("closingPrioritaryC").toBool());
        ui->openningPrioritaryC->setChecked(!(settings->value("closingPrioritaryC").toBool()));
    }
    if (settings->contains("filterSizeC")) ui->filterSizeC->setValue(settings->value("filterSizeC").toInt());
    if (settings->contains("closingSizeC")) ui->closingSizeC->setValue(settings->value("closingSizeC").toInt());
    if (settings->contains("openningSizeC")) ui->openningSizeC->setValue(settings->value("openningSizeC").toInt());
    if (settings->contains("openningRepetitionsC")) ui->openningRepetitionsC->setValue(settings->value("openningRepetitionsC").toInt());
    if (settings->contains("closingRepetitionsC")) ui->closingRepetitionsC->setValue(settings->value("closingRepetitionsC").toInt());

    if (settings->contains("doFindContoursD")) ui->findContoursD->setChecked(settings->value("doFindContoursD").toBool());
    if (settings->contains("doCannyD")) ui->cannyD->setChecked(settings->value("doCannyD").toBool());
    if (settings->contains("doMinPerimeterD")) ui->doMinPerimeterD->setChecked(settings->value("doMinPerimeterD").toBool());
    if (settings->contains("minPerimeterD")) ui->minPerimeterD->setValue(settings->value("minPerimeterD").toInt());
    if (settings->contains("thicknessD")) ui->thicknessD->setValue(settings->value("thicknessD").toInt());
    if (settings->contains("cannyLowThresholdD")) ui->cannyLowThresholdD->setValue(settings->value("cannyLowThresholdD").toInt());
    if (settings->contains("cannyHighThresholdD")) ui->cannyHighThresholdD->setValue(settings->value("cannyHighThresholdD").toInt());

    if (settings->contains("stepRadiiE")) ui->stepRadiiE->setValue(settings->value("stepRadiiE").toInt());
    if (settings->contains("stepAngleE")) ui->stepAngleE->setValue(settings->value("stepAngleE").toInt());
    if (settings->contains("thresholdE")) ui->thresholdE->setValue(settings->value("thresholdE").toInt());
    if (settings->contains("miniRoadAngleE")) ui->miniRoadAngleE->setValue(settings->value("miniRoadAngleE").toInt());

    if (settings->contains("fourPointsRatioF")) ui->fourPointsRatioF->setValue(settings->value("fourPointsRatioF").toDouble());
    if (settings->contains("resultSizeRatioF")) ui->resultSizeRatioF->setValue(settings->value("resultSizeRatioF").toDouble());
    if (settings->contains("resolutionRatioF")) ui->resolutionRatioF->setValue(settings->value("resolutionRatioF").toInt());

    if (settings->contains("aG")) ui->aG->setValue(settings->value("aG").toDouble());
    if (settings->contains("bG")) ui->bG->setValue(settings->value("bG").toDouble());
    if (settings->contains("avGaussBlurG")) {
        ui->averageBlurG->setChecked(settings->value("avGaussBlurG").toBool());
        ui->gaussianBlurG->setChecked(!settings->value("avGaussBlurG").toBool());
    }
    if (settings->contains("blurSizeG")) ui->blurSizeG->setValue(settings->value("blurSizeG").toInt());

    if (settings->contains("shiftingRigidityH")) ui->shiftingRigidityH->setValue(settings->value("shiftingRigidityH").toInt());
    if (settings->contains("widthRigidityH")) ui->widthRigidityH->setValue(settings->value("widthRigidityH").toInt());
    if (settings->contains("maxWidthDifferenceH")) ui->maxWidthDifferenceH->setValue(settings->value("maxWidthDifferenceH").toInt());
    if (settings->contains("cutColorH")) ui->cutColorH->setChecked(settings->value("cutColorH").toBool());
    if (settings->contains("cuttingLimitH")) ui->cuttingLimitH->setValue(settings->value("cuttingLimitH").toInt());
    if (settings->contains("transparencyH")) ui->transparencyH->setValue(settings->value("transparencyH").toInt());

}

View::~View()
{
    delete ui;
    delete settings;
}


void View::on_chargerButton_clicked() {
    QString filename = QFileDialog::getOpenFileName(this, "Open File", QDir::currentPath(), "Images (*.png *.xpm *.jpg *.bmp)") ;
    if (filename.compare("") != 0){
        imageProcessing.setImage(filename.toStdString());
        QImage img(filename) ;
        if (img.width() > 700)
            img= img.scaledToWidth(700);
        ui->image0->setPixmap(QPixmap::fromImage(img));
        imageLoaded = true ;
        showSample();
        ui->processButton->setEnabled(true);
    }
}


void View::showSample() {
    if (imageLoaded) {
        QImage img = imageProcessing.getSampleQImage();
        ui->sample->setPixmap(QPixmap::fromImage(img));
        ui->sample->setMinimumWidth(img.width());
        ui->sample->setMinimumHeight(img.height());
        ui->sample->setEnabled(true);
        ui->sampleLabel->setEnabled(true);
    }
}


void View::on_processButton_clicked() {
    ui->centralwidget->setDisabled(true);
    ui->statusbar->showMessage("Processing");
    imageProcessing.start();
}


void View::on_enregistrerButton_clicked() {
    QString fileSavedName = QFileDialog::getSaveFileName(ui->centralwidget, "Enregistrer l'image sous...");
    QFile file(fileSavedName);
    if (!file.open(QIODevice::ReadWrite))
        return;
    QImage img = imageProcessing.getResult() ;
    img.save(&file) ;
    file.close();
}

void View::on_checkA_toggled(bool b) {
    imageProcessing.setDoA(b);
}

void View::on_checkB_toggled(bool b) {
    if (!b){
        ui->checkC->setChecked(false);
        ui->checkD->setChecked(false);
        ui->checkE->setChecked(false);
    }
    imageProcessing.setDoB(b);
}

void View::on_checkC_toggled(bool b) {
    imageProcessing.setDoC(b);
    if (b) ui->checkB->setChecked(true);
}

void View::on_checkD_toggled(bool b) {
    imageProcessing.setDoD(b);
    if (b) ui->checkB->setChecked(true);
}

void View::on_checkE_toggled(bool b) {
    imageProcessing.setDoE(b);
    if (b) {
        ui->checkB->setChecked(true);
        ui->checkC->setChecked(true);
        ui->checkF->setChecked(false);
    }
}

void View::on_checkF_toggled(bool b) {
    imageProcessing.setDoF(b);
    if (b) {
        ui->checkB->setChecked(true);
        ui->checkC->setChecked(true);
        ui->checkE->setChecked(false);
    } else
        ui->checkG->setChecked(false);
}

void View::on_checkG_toggled(bool b) {
    imageProcessing.setDoG(b);
    if (b)
        ui->checkF->setChecked(true);
    else
        ui->checkH->setChecked(false);
}

void View::on_checkH_toggled(bool b) {
    imageProcessing.setDoH(b);
    if (b)
        ui->checkG->setChecked(true);
    else
        ui->checkI->setChecked(false);
}

void View::on_checkI_toggled(bool b) {
    imageProcessing.setDoI(b);
    if (b)
        ui->checkH->setChecked(true);
}

void View::on_medianFilterA_toggled(bool b){
    imageProcessing.setDoMedianFilterA(b);
}

void View::on_lowPassFilterA_toggled(bool b){
    imageProcessing.setDoLowPassFilterA(b);
}

void View::on_filterSizeA_valueChanged(int i){
    imageProcessing.setFilterSizeA(i);
}

void View::on_graySpaceB_toggled(bool b){
    if (b) {
        colorSpaceB = 0 ;
        imageProcessing.setColorSpaceB(0); }
}

void View::on_bgrSpaceB_toggled(bool b){
    if (b) {
        colorSpaceB = 1 ;
        imageProcessing.setColorSpaceB(1); }
}

void View::on_cieSpaceB_toggled(bool b){
    if (b) {
        colorSpaceB = 2 ;
        imageProcessing.setColorSpaceB(2); }
}

void View::on_hsvSpaceB_toggled(bool b){
    if (b) {
        colorSpaceB = 3 ;
        imageProcessing.setColorSpaceB(3); }
}

void View::on_ycrcbSpaceB_toggled(bool b){
    if (b) {
        colorSpaceB = 4 ;
        imageProcessing.setColorSpaceB(4); }
}

void View::on_backprojectingB_toggled(bool b){
    if (b)
        ui->distanceFilterB->setChecked(false);
    imageProcessing.setDoBackProjectingB(b);
}

void View::on_distanceFilterB_toggled(bool b){
    if (b)
        ui->backprojectingB->setChecked(false);
    imageProcessing.setDoDistanceFilterB(b);
}

void View::on_backprojectingTresholdB_valueChanged(int i){
    imageProcessing.setBackprojectingTresholdB(i);
}

void View::on_distanceFilterTresholdB_valueChanged(int i){
    imageProcessing.setDistanceFilterTresholdB(i);
}

void View::on_samplePosxB_valueChanged(int i) {
    imageProcessing.setSamplePosxB(i);
    showSample();
}

void View::on_samplePosyB_valueChanged(int i) {
    imageProcessing.setSamplePosyB(i);
    showSample();
}

void View::on_sampleSizeB_valueChanged(int i) {
    imageProcessing.setSampleSizeB(i);
    showSample();
}

void View::on_medianFilterC_toggled(bool b) {
    imageProcessing.setDoMedianFilterC(b);
}

void View::on_filterSizeC_valueChanged(int i) {
    imageProcessing.setFilterSizeC(i);
}

void View::on_closingC_toggled(bool b) {
    imageProcessing.setDoClosing(b);
}

void View::on_closingPrioritaryC_toggled(bool b) {
    imageProcessing.setClosingPrioritaryC(b);
}

void View::on_openningC_toggled(bool b) {
    imageProcessing.setDoOpenning(b);
}

void View::on_closingSizeC_valueChanged(int i) {
    imageProcessing.setClosingSizeC(i);
}

void View::on_openningSizeC_valueChanged(int i) {
    imageProcessing.setOpenningSizeC(i);
}

void View::on_closingRepetitionsC_valueChanged(int i) {
    imageProcessing.setClosingRepetitionsC(i);
}

void View::on_openningRepetitionsC_valueChanged(int i) {
    imageProcessing.setOpenningRepetitionsC(i);
}

void View::on_findContoursD_toggled(bool b) {
    if (b) ui->cannyD->setChecked(false);
    imageProcessing.setDoFindContoursD(b);
}

void View::on_doMinPerimeterD_toggled(bool b) {
    imageProcessing.setDoMinPerimeterD(b);
}

void View::on_cannyD_toggled(bool b) {
    if (b) ui->findContoursD->setChecked(false);
    imageProcessing.setDoCannyD(b);
}

void View::on_minPerimeterD_valueChanged(int i) {
    imageProcessing.setMinPerimeterD(i);
}

void View::on_thicknessD_valueChanged(int i) {
    imageProcessing.setThicknessD(i);
}

void View::on_cannyHighThresholdD_valueChanged(int i) {
    imageProcessing.setCannyHighThresholdD(i);
}

void View::on_cannyLowThresholdD_valueChanged(int i) {
    imageProcessing.setCannyLowThresholdD(i);
}

void View::on_stepRadiiE_valueChanged(int i) {
    imageProcessing.setStepRadiiE(i);
}

void View::on_stepAngleE_valueChanged(int i) {
    imageProcessing.setStepAngleE(i);
}

void View::on_thresholdE_valueChanged(int i) {
    imageProcessing.setThresholdE(i);
}

void View::on_miniRoadAngleE_valueChanged(int i) {
    imageProcessing.setMiniRoadAngleE(i);
}

void View::on_fourPointsRatioF_valueChanged(double d) {
    imageProcessing.setFourPointsRatioF(d);
}

void View::on_resultSizeRatioF_valueChanged(double d) {
    imageProcessing.setResultSizeRatioF(d);
}

void View::on_resolutionRatioF_valueChanged(int i) {
    imageProcessing.setResolutionRatioF(i);
}

void View::on_aG_valueChanged(double d) {
    imageProcessing.setAG(d);
}

void View::on_bG_valueChanged(double d) {
    imageProcessing.setBG(d);
}

void View::on_averageBlurG_toggled(bool b) {
    imageProcessing.setAvGaussBlurG(b);
}

void View::on_blurSizeG_valueChanged(int i) {
    imageProcessing.setBlurSizeG(i);
}

void View::on_shiftingRigidityH_valueChanged(int i) {
    imageProcessing.setShiftingRigidityH(i);
}

void View::on_widthRigidityH_valueChanged(int i) {
    imageProcessing.setWidthRigidityH(i);
}

void View::on_maxWidthDifferenceH_valueChanged(int i) {
    imageProcessing.setMaxWidthDifferenceH(i);
}

void View::on_cutColorH_toggled(bool b) {
    imageProcessing.setCutColorH(b);
}

void View::on_cuttingLimitH_valueChanged(int i) {
    imageProcessing.setCuttingLimitH(i);
}

void View::on_transparencyH_valueChanged(int i) {
    imageProcessing.setTransparencyH(i);
}


void View::on_saveSettings_clicked() {
    settings->setValue("doA", ui->checkA->isChecked());
    settings->setValue("doB", ui->checkB->isChecked());
    settings->setValue("doC", ui->checkC->isChecked());
    settings->setValue("doD", ui->checkD->isChecked());
    settings->setValue("doE", ui->checkE->isChecked());
    settings->setValue("doF", ui->checkF->isChecked());
    settings->setValue("doG", ui->checkG->isChecked());
    settings->setValue("doH", ui->checkH->isChecked());
    settings->setValue("doI", ui->checkI->isChecked());
    settings->setValue("doMedianFilterA", ui->medianFilterA->isChecked());
    settings->setValue("doLowPassFilterA", ui->lowPassFilterA->isChecked());
    settings->setValue("filterSizeA", ui->filterSizeA->value());
    settings->setValue("colorSpaceB", colorSpaceB);
    settings->setValue("doBackprojectingB", ui->backprojectingB->isChecked());
    settings->setValue("doDistanceFilterB", ui->distanceFilterB->isChecked());
    settings->setValue("backprojectingTresholdB", ui->backprojectingTresholdB->value());
    settings->setValue("distanceFilterTresholdB", ui->distanceFilterTresholdB->value());
    settings->setValue("samplePosxB", ui->samplePosxB->value());
    settings->setValue("samplePosyB", ui->samplePosyB->value());
    settings->setValue("sampleSizeB", ui->sampleSizeB->value());
    settings->setValue("doMedianFilterC", ui->medianFilterC->isChecked());
    settings->setValue("filterSizeC", ui->filterSizeC->value());
    settings->setValue("doClosingC", ui->closingC->isChecked());
    settings->setValue("doOpenningC", ui->openningC->isChecked());
    settings->setValue("closingPrioritaryC", ui->closingPrioritaryC->isChecked());
    settings->setValue("closingSizeC", ui->closingSizeC->value());
    settings->setValue("openningSizeC", ui->openningSizeC->value());
    settings->setValue("openningRepetitionsC", ui->openningRepetitionsC->value());
    settings->setValue("closingRepetitionsC", ui->closingRepetitionsC->value());
    settings->setValue("doFindContoursD", ui->findContoursD->isChecked());
    settings->setValue("doCannyD", ui->cannyD->isChecked());
    settings->setValue("doMinPerimeterD", ui->doMinPerimeterD->isChecked());
    settings->setValue("minPerimeterD", ui->minPerimeterD->value());
    settings->setValue("thicknessD", ui->thicknessD->value());
    settings->setValue("cannyLowThresholdD", ui->cannyLowThresholdD->value());
    settings->setValue("cannyHighThresholdD", ui->cannyHighThresholdD->value());
    settings->setValue("stepRadiiE", ui->stepRadiiE->value());
    settings->setValue("stepAngleE", ui->stepAngleE->value());
    settings->setValue("thresholdE", ui->thresholdE->value());
    settings->setValue("miniRoadAngleE", ui->miniRoadAngleE->value());
    settings->setValue("fourPointsRatioF", ui->fourPointsRatioF->value());
    settings->setValue("resultSizeRatioF", ui->resultSizeRatioF->value());
    settings->setValue("resolutionRatioF", ui->resolutionRatioF->value());
    settings->setValue("aG", ui->aG->value());
    settings->setValue("bG", ui->bG->value());
    settings->setValue("avGaussBlurG", ui->averageBlurG->isChecked());
    settings->setValue("blurSizeG", ui->blurSizeG->value());
    settings->setValue("shiftingRigidityH", ui->shiftingRigidityH->value());
    settings->setValue("widthRigidityH", ui->widthRigidityH->value());
    settings->setValue("maxWidthDifferenceH", ui->maxWidthDifferenceH->value());
    settings->setValue("cutColorH", ui->cutColorH->isChecked());
    settings->setValue("cuttingLimitH", ui->cuttingLimitH->value());
    settings->setValue("transparencyH", ui->transparencyH->value());
}



void View::updateResults() {
    QImage img = imageProcessing.getResult() ;
    if (img.width()>img.height()){
        if (img.width() > 700)
            img= img.scaledToWidth(700);
    } else {
        if (img.height() > 700)
            img= img.scaledToHeight(700);
    }
    ui->image1->setPixmap(QPixmap::fromImage(img));
    ui->centralwidget->setEnabled(true);
    ui->statusbar->showMessage("Traitement de l'image fini");
}

