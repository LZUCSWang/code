import sys
from PyQt5.QtWidgets import *

app = QApplication(sys.argv)
lab1 = QLabel()
lab1.resize(300, 200)
lab1.setText('Hello, World!')
lab1.show()
app.exec_()