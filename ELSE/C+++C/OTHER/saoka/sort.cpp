ui->target_spinBox->setMinimum(nMin);  // 最小值
    ui->target_spinBox->setMaximum(nMax);  // 最大值
    ui->target_spinBox->setSingleStep(nSingleStep);  // 步长

    ui->target_horizontalSlider->setMinimum(nMin);  // 最小值
    ui->target_horizontalSlider->setMaximum(nMax);  // 最大值
    ui->target_horizontalSlider->setSingleStep(nSingleStep);  // 步长

    connect(ui->target_spinBox, SIGNAL(valueChanged(int)), ui->target_horizontalSlider, SLOT(setValue(int)));
    connect(ui->target_horizontalSlider, SIGNAL(valueChanged(int)), ui->target_spinBox, SLOT(setValue(int)));