#include <iostream>
#include <vector>
#include <memory>

#include "h/organ.h"
#include "h/app.h"
#include "h/voice.h"

constexpr int KEYBOARDS_COUNT = 6;

static void printVoicesState(std::vector<std::shared_ptr<voice>>& voices) {
    std::cout << "STATE: ";

    for (auto& v : voices) {
        auto current = v.get();
        std::cout << current->isOn() << " ";
    }

    std::cout << "\n";
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, nullptr);

    try {
        std::cout << "CREATING INSTRUMENT..." << "\n";
        organ instrument(KEYBOARDS_COUNT);

        std::cout << "LOADING DEVICES..." << "\n";
        std::vector<std::unique_ptr<MIDI_controller>> devices = detectDevices();

        int deviceCount = static_cast<int>(devices.size());
        int sectionCount = 3;
        int limit = std::min(deviceCount, sectionCount);

        std::cout << " >> Active device count: " << deviceCount << "\n";

        std::cout << "CREATING VOICES..." << "\n";
        auto prinzipal8 = std::make_shared<voice>(0, "Prinzipal 8'");
        auto floete8 = std::make_shared<voice>(1, "Floete 8'");
        auto gambe4 = std::make_shared<voice>(2, "Gambe 4'");
        auto octave4 = std::make_shared<voice>(3, "Octave 4'");
        auto octave2 = std::make_shared<voice>(4, "Octave 2'");
        auto quinte2_23 = std::make_shared<voice>(5, "Quinte 2 2/3'");
        auto terz1_35 = std::make_shared<voice>(6, "Terz 1 3/5'");
        auto subbass16 = std::make_shared<voice>(7, "Subbass 16'");
        auto violon16 = std::make_shared<voice>(8, "Violon 16'");

        std::vector<std::shared_ptr<voice>> allVoices =
            { prinzipal8, floete8, gambe4, octave4, octave2, quinte2_23, terz1_35, subbass16, violon16 };

        printVoicesState(allVoices);
        
        std::cout << "CREATING SECTIONS..." << "\n";
        std::vector<std::shared_ptr<section>> sections;
        std::vector<std::shared_ptr<voice>> v1 = { prinzipal8, octave4, octave2, quinte2_23 };
        sections.push_back(std::make_shared<section>("Hauptwerk", v1));
        std::vector<std::shared_ptr<voice>> v2 = { floete8, gambe4, terz1_35 };
        sections.push_back(std::make_shared<section>("Oberwerk", v2));
        std::vector<std::shared_ptr<voice>> v3 = { subbass16, violon16 };
        sections.push_back(std::make_shared<section>("Pedal", v3));        

        std::cout << "CREATING VOICE GROUPS..." << "\n";
        std::vector<std::shared_ptr<voiceGroup>> voiceGroups;
        std::vector<std::shared_ptr<voice>> g1 = { quinte2_23, terz1_35 };
        voiceGroups.push_back(std::make_shared<voiceGroup>(g1));

        std::cout << "ASSIGNING DEVICES TO KEYBOARDS..." << "\n";
        for (int i = 0; i < limit; i++) {
            auto currentDevice = devices[i].get();
            auto& currentSection = sections[i];

            instrument.getKeyboards()[i]->setDevice(currentDevice);
            instrument.getKeyboards()[i]->setSection(currentSection.get());

            std::cout << " >> Assigned keyboard " << i
                << ": controller " << currentDevice->getDeviceName()
                << " <= to => section " << currentSection->getName() << "\n";
        }

        auto& keyboards = instrument.getKeyboards();
        int keyboardCount = instrument.getKeyboardCount();

        std::cout << "RUNNING..." << "\n";

        while (true) {
            for (int i = 0; i < keyboardCount; i++) {
                auto currentController = keyboards[i]->getDevice();
                if (!currentController) continue;

                MIDI_packet msg = currentController->readMessage();
                if (msg.status == 0) continue;

                std::cout << currentController->getDeviceName() << ": "
                    << static_cast<int>(msg.note) << " "
                    << static_cast<int>(msg.status) << " "
                    << static_cast<int>(msg.velocity) << "\n";
            }
        }
    }
    catch (RtMidiError& rtError) {
        rtError.printMessage();
    }

    return 0;
}
