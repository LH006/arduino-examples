import sys

from PyQt6.QtCore import QSize, Qt
from PyQt6.QtWidgets import QApplication, QWidget, QMainWindow, QPushButton, QLabel, QLineEdit, QVBoxLayout

class MyApp(QMainWindow):

    def __init__(self):
        super().__init__() #QWidget()
        self.initUI()

    def initUI(self):
        self.setWindowTitle("MyApp")

        self.label = QLabel()

        self.input = QLineEdit()
        self.input.textChanged.connect(self.label.setText)

        button = QPushButton("Press Me!")
        button.setCheckable(True)

        button.clicked.connect(self.button_clicked)
        button.clicked.connect(self.button_toggled)

        layout = QVBoxLayout()
        layout.addWidget(self.input)
        layout.addWidget(self.label)
        layout.addWidget(button)

        container = QWidget()
        container.setLayout(layout)

        self.setCentralWidget(container)
    
    def button_clicked(self):
        print("nihehe")

    def button_toggled(self,checked):
        print(f"Checked: {checked}")

def main():
    app = QApplication(sys.argv)
    window = MyApp()
    window.show()

    # Start the event loop
    app.exec()

if __name__ == '__main__':
    main()