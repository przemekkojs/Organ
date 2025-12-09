import sys
import random
from organ import *

from PySide6 import QtCore
from PySide6.QtGui import QAction
from PySide6.QtWidgets import QApplication, QMainWindow, QWidget,\
                              QVBoxLayout, QMenuBar, QMenu, QLineEdit,\
                              QPushButton, QGroupBox, QHBoxLayout

class LoadInstrument(QWidget):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Załaduj instrument")
        self.setMinimumSize(300, 300)


class SoundSettings(QWidget):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Dźwięk")
        self.setMinimumSize(300, 300)


class MIDISettings(QWidget):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("MIDI")
        self.setMinimumSize(300, 300)


class About(QWidget):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("O programie")
        self.setMinimumSize(300, 300)


class Piston(QWidget):
    def __init__(self):
        super().__init__()


class Section(QWidget):
    def __init__(self):
        super().__init__()

        self.pistons = []


class Keyboard(QWidget):
    def __init__(self):
        super().__init__()

    
class Piston(QWidget):
    def __init__(self):
        super().__init__()


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Organ")
        self.setMinimumSize(600, 400)

        self.central_widget = QWidget()
        self.selfLayout = QVBoxLayout()
        self.central_widget.setLayout(self.selfLayout)
        self.setCentralWidget(self.central_widget)

        self.menu_bar = self.menuBar()

        self.file_menu = self.menu_bar.addMenu("Plik")
        self.file_menu.addAction(QAction("Zapisz", self))
        self.file_menu.addAction(QAction("Załaduj instrument", self))

        self.panel_menu = self.menu_bar.addMenu("Panel")
        self.panel_menu.addAction(QAction("Klawiatury", self))
        self.panel_menu.addAction(QAction("Manubria", self))
        self.panel_menu.addAction(QAction("Kombinacje", self))

        self.settings_menu = self.menu_bar.addMenu("Ustawienia")
        self.settings_menu.addAction(QAction("Dźwięk", self))
        self.settings_menu.addAction(QAction("MIDI", self))

        self.help_menu = self.menu_bar.addMenu("Pomoc")
        self.help_menu.addAction(QAction("O programie", self))

        # TEMPORARY:
        # self.organ = organ()

        self.voice_count:int = 0
        self.section_count:int = 0
        self.keyboard_count:int = 0
        self.voice_group_count:int = 0

        self.section_gb = QGroupBox()
        self.section_gb_l = QHBoxLayout()
        self.section_add_button = QPushButton()
        self.section_add_button.setText(f"Dodaj sekcję {self.sCount()}")
        self.section_gb_l.addWidget(self.section_add_button)
        self.section_gb.setLayout(self.section_gb_l)

        self.voice_group_gb = QGroupBox()
        self.voice_group_gb_l = QHBoxLayout()
        self.voice_group_add_button = QPushButton()
        self.voice_group_add_button.setText(f"Dodaj grupę głosów {self.vgCount()}")
        self.voice_group_gb_l.addWidget(self.voice_group_add_button)
        self.voice_group_gb.setLayout(self.voice_group_gb_l)

        self.selfLayout.addWidget(self.section_gb)
        self.selfLayout.addWidget(self.voice_group_gb)

        self.midiSettings = MIDISettings()
        self.soundSettings = SoundSettings()
        self.about = About()
        self.loadInstrument = LoadInstrument()

        self.voice_group_add_button.clicked.connect(self.add_voice_group)
        self.section_add_button.clicked.connect(self.add_section)

    def add_section(self):
        sectionSount = self.sCount()
        # to_add:section = section(f"Sekcja {sectionSount}")    
        # self.organ.addSection(to_add)
        self.section_add_button.setText(f"Dodaj sekcję {sectionSount}")        

    def add_keyboard(self):
        pass

    def add_voice_group(self):
        voiceGroupCount = self.vgCount()
        # to_add = voiceGroup(f"Grupa głosów {voiceGroupCount}")
        # self.organ.addVoiceGroup(to_add)
        self.voice_group_add_button.setText(f"Dodaj grupę głosów {voiceGroupCount}")
        

    def vgCount(self) -> int:
        return random.randint(0, 10000) #self.organ.getVoiceGroupCount()
    
    def sCount(self) -> int:
        return random.randint(0, 10000) #self.organ.getSectionCount()
    
    def kCount(self) -> int:
        return random.randint(0, 10000) #self.organ.getKeyboardsCount()


def main():
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())

if __name__ == '__main__':
    main()
