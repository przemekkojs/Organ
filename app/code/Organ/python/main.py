import sys
import random
from organ import *

from PySide6 import QtCore
from PySide6.QtGui import QAction
from PySide6.QtWidgets import QApplication, QMainWindow, QWidget,\
                              QVBoxLayout, QMenuBar, QMenu, QLineEdit,\
                              QPushButton, QGroupBox, QHBoxLayout,\
                              QTextBrowser, QDialog, QLabel

class LoadInstrument(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)

        self.setWindowTitle("Załaduj instrument")
        self.setMinimumSize(300, 300)


class SoundSettings(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)

        self.setWindowTitle("Dźwięk")
        self.setMinimumSize(300, 300)


class MIDISettings(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)

        self.setWindowTitle("MIDI")
        self.setMinimumSize(300, 300)


class About(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)

        self.selfLayout = QVBoxLayout()
        self.setWindowTitle("O programie")
        self.textBrowser = QTextBrowser()
        self.textBrowser.setText("Organ - symulator wirtualnych organów piszczałkowych")
        
        self.setLayout(self.selfLayout)
        self.selfLayout.addWidget(self.textBrowser)


class Piston(QWidget):
    def __init__(self, text:str):#, piston:piston):
        super().__init__()
        #self.piston = piston
        self.setFixedSize(100, 100)

        self.button = QPushButton()
        self.button.setText(text)
        self.on_diode = QLabel()
        
        self.setLayout(QVBoxLayout())
        self.layout().addWidget(self.on_diode)
        self.layout().addWidget(self.button)

        self.setDiode()
        self.button.clicked.connect(self.press)

    def setDiode(self):
        to_set:str = "□" if self.on_diode.text() == "■" else "■" #self.piston.isOn() else "■"
        self.on_diode.setText(to_set)

    def press(self):
        # self.pison.press()
        self.setDiode()


class Section(QWidget):
    def __init__(self, name:str):
        super().__init__()

        # self.section = section(name)
        self.pistons = []
        self.setLayout(QVBoxLayout())

        self.layout().addWidget(QLabel(name))

        self.add_piston_button = QPushButton()
        self.add_piston_button.setText("Dodaj piston")
        self.add_piston_button.clicked.connect(lambda: self.add(str(random.randint(1, 10000))))
        self.layout().addWidget(self.add_piston_button)

        self.pistons_gb = QGroupBox()
        self.pistons_layout = QHBoxLayout()
        self.pistons_gb.setLayout(self.pistons_layout)
        self.layout().addWidget(self.pistons_gb)

    def add(self, text:str):
        to_add = Piston(text)
        self.pistons.append(to_add)
        self.pistons_layout.addWidget(to_add)


class Keyboard(QWidget):
    def __init__(self, keyboard, number_of_keys):
        super().__init__()
        self.keyboard = keyboard

        self.number_of_keys = number_of_keys
        self.keys = []


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
        self.save_action = QAction("Zapisz", self)
        self.load_instrument_action = QAction("Załaduj instrument", self)
        self.load_instrument_action.triggered.connect(self.show_load_instrument_window)
        
        for item in [self.save_action, self.load_instrument_action]:
            self.file_menu.addAction(item)

        self.panel_menu = self.menu_bar.addMenu("Panel")
        self.keyboards_action = QAction("Klawiatury", self)
        self.pistons_action = QAction("Manubria", self)
        self.combinations_action = QAction("Kombinacje", self)
        
        for item in [self.keyboards_action, self.pistons_action, self.combinations_action]:
            self.panel_menu.addAction(item)

        self.settings_menu = self.menu_bar.addMenu("Ustawienia")
        self.sound_action = QAction("Dźwięk", self)
        self.sound_action.triggered.connect(self.show_sound_settings_window)
        self.midi_action = QAction("MIDI", self)
        self.midi_action.triggered.connect(self.show_midi_settings_window)

        for item in [self.sound_action, self.midi_action]:
            self.settings_menu.addAction(item)

        self.help_menu = self.menu_bar.addMenu("Pomoc")
        self.about_action = QAction("O programie", self)
        self.about_action.triggered.connect(self.show_about_window)

        for item in [self.about_action]:
            self.help_menu.addAction(item)

        # TEMPORARY:
        # self.organ = organ()

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

        self.voice_group_add_button.clicked.connect(self.add_voice_group)
        self.section_add_button.clicked.connect(self.add_section)

    def add_section(self):
        sectionSount = self.sCount()
        # to_add:section = section(f"Sekcja {sectionSount}")    
        # self.organ.addSection(to_add)

        s = Section(f"Sekcja {sectionSount}")
        self.section_gb_l.addWidget(s)
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
    
    def show_about_window(self):
        self.about_window = About(parent=self)
        self.about_window.show()

    def show_midi_settings_window(self):
        self.midi_settings_window = MIDISettings(parent=self)
        self.midi_settings_window.show()

    def show_sound_settings_window(self):
        self.sound_settings_window = SoundSettings(parent=self)
        self.sound_settings_window.show()

    def show_load_instrument_window(self):
        self.load_instrument_window = LoadInstrument(parent=self)
        self.load_instrument_window.show()

def main():
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())

if __name__ == '__main__':
    main()
