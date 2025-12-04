import sys
# from organ import *

from PySide6 import QtCore
from PySide6.QtGui import QAction
from PySide6.QtWidgets import QApplication, QMainWindow, QWidget,\
                              QVBoxLayout, QMenuBar, QMenu

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Organ")
        self.setMinimumSize(400, 400)

        central_widget = QWidget()
        layout = QVBoxLayout()
        central_widget.setLayout(layout)
        self.setCentralWidget(central_widget)

        menu_bar = self.menuBar()

        file_menu = menu_bar.addMenu("Plik")
        file_menu.addAction(QAction("Zapisz", self))
        file_menu.addAction(QAction("Załaduj instrument", self))

        panel_menu = menu_bar.addMenu("Panel")
        panel_menu.addAction(QAction("Klawiatury", self))
        panel_menu.addAction(QAction("Manubria", self))
        panel_menu.addAction(QAction("Kombinacje", self))

        settings_menu = menu_bar.addMenu("Ustawienia")
        settings_menu.addAction(QAction("Dźwięk", self))
        settings_menu.addAction(QAction("MIDI", self))

        help_menu = menu_bar.addMenu("Pomoc")
        help_menu.addAction(QAction("O programie", self))


def main():
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())

if __name__ == '__main__':
    main()
