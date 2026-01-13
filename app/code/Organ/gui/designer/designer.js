const mainContainer = document.getElementById('main-container');

const leftContainer = document.getElementById('left-container');
const leftContainerContent = document.getElementById('l-c-content');
const leftContainerButtonContainer = document.getElementById('l-c-button-container');
const leftContainerButton = document.getElementById('l-c-button');

const centerContainer = document.getElementById('center-container');
const centerContainerInfo = document.getElementById('c-c-info');
const centerContainerInfoUsages = document.getElementById('c-c-i-usages');
const centerContainerInfoInstrumentName = document.getElementById('c-c-i-instrument-name');
const centerContainerInfoRamUsage = document.getElementById('c-c-i-ram-usage');
const centerContainerInfoCpuUsage = document.getElementById('c-c-i-cpu-usage');
const centerContainerManuals = document.getElementById('c-c-manuals-container');
const centerContainerManualsContent = document.getElementById('c-c-m-c-content');
const centerContainerManualsButtonContainer = document.getElementById('c-c-m-c-button-container');
const centerContainerManualsButton = document.getElementById('c-c-e-c-button');
const centerContainerExpression = document.getElementById('c-c-expression-container');
const centerContainerExpressionContent = document.getElementById('c-c-e-c-content');
const centerContainerExpressionButtonContainer = document.getElementById('c-c-e-c-button-container');
const centerContainerExpressionButton = document.getElementById('c-c-e-c-button');
const centerContainerPedal = document.getElementById('c-c-pedal-container');
const centerContainerPedalContent = document.getElementById('c-c-p-c-content');
const centerContainerPedalButtonsContainer = document.getElementById('c-c-p-c-buttons-container');

const rightContainer = document.getElementById('right-container');
const rightContainerContent = document.getElementById('r-c-content');
const rightContainerButtonContainer = document.getElementById('r-c-button-container');
const rightContainerButton = document.getElementById('l-c-button');

function debug(event) {
    console.log("Zostałem wywołany(a)!", event);
}

function loadInstrument() {
    const name = "INSTRUMENT";
    const ramUsage = "4/8 GB";
    const cpuUsage = "50%";

    centerContainerInfoInstrumentName.innerText = name;
    centerContainerInfoRamUsage.innerText = `Zużycie RAM: ${ramUsage}`;
    centerContainerInfoCpuUsage.innerText = `Zużycie CPU: ${cpuUsage}`;
}

function printList(l) {
    console.log("=================")

    l.forEach(element => {
        console.log(element);
    });

    console.log("=================")
}

const keyboards = [];
const pistons = [];
const sections = [];
const voices = [];
const expressions = [];

const defaultNumberOfKeysManual = 61;
const defaultNumberOfKeysPedal = 32;

// ==============
// == KEYBOARD ==
// ==============

class keyboard {
    id;
    numberOfKeys = defaultNumberOfKeysManual;

    constructor(id, numberOfKeys) {
        this.id = id;
        this.numberOfKeys = numberOfKeys;

        this.section = null;
        this.htmlElement = document.createElement('div');
        this.htmlElement.id = `keyboard-${this.id}`;
        this.htmlElement.className = "horizontal-container";

        this.htmlElement.innerHTML = `
            <div id="keyboard-${this.id}-caption">
                Klawiatura ${this.id}
            </div>

            <div class="vertical-container">
                <input type="button" value="⚙" id="settings-keyboard-${this.id}" onclick="keyboardSettings(${this.id})">
                <input type="button" value="🗑" id="remove-keyboard-${this.id}" onclick="removeKeyboard(${this.id})">
            </div>
        `;
    }

    press(keyNumber) {
        if (keyNumber > this.numberOfKeys)
            return;

        console.log(`Klawiatura ${this.id}: ${keyNumber}`);
        this.section.press(keyNumber);
    }

    setId(val) {        
        document.getElementById(`keyboard-${this.id}-caption`).innerText = `Klawiatura ${val}`;
        document.getElementById(`remove-keyboard-${this.id}`).onclick = () => removeKeyboard(val);
        document.getElementById(`settings-keyboard-${this.id}`).onclick = () => keyboardSettings(val);

        document.getElementById(`keyboard-${this.id}`).id = `keyboard-${val}`;
        document.getElementById(`keyboard-${this.id}-caption`).id = `keyboard-${val}-caption`;
        document.getElementById(`remove-keyboard-${this.id}`).id = `remove-keyboard-${val}`;
        document.getElementById(`settings-keyboard-${this.id}`).id = `settings-keyboard-${val}`;

        this.id = val;
    }

    assignSection(sect) {
        this.section = sect;
    }
}

function addKeyboard() {
    let nextId = keyboards.length;    
    let toAdd = new keyboard(nextId);

    keyboards.push(toAdd);
    centerContainerManualsContent.appendChild(toAdd.htmlElement);
}

function removeKeyboard(id) {
    if (window.confirm(`Czy na pewno usunąć klawiaturę ${id}?`)) {
        elem = keyboards.splice(id, 1)[0];
        centerContainerManualsContent.removeChild(elem.htmlElement);

        for (let i = id; i < keyboards.length; i++) {
            current = keyboards[i];
            current.setId(i);
        }
    }    
}

function keyboardSettings(id) {
    window.alert(`Tutaj byłoby okienko ustawień klawiatury ${id}`);
}

// ============
// == PISTON ==
// ============

class piston {
    id;
    name;
    controlledElements;

    constructor(id, name) {
        this.id = id;
        this.name = name;
        this.controlledElements = [];

        this.htmlElement = document.createElement('div');
        this.htmlElement.className = "";
        this.htmlElement.id = `piston-${this.id}`;
        this.htmlElement.innerHTML = `
            <div>
                <div>
                    <span id="piston-${this.id}-name">${this.name}</span>
                    <input type="button" value="O" id="piston-${this.id}-button" onclick="${() => this.press}">
                </div>
                
                <div>
                    <input type="button" value="⚙" id="piston-${this.id}-settings" onclick="pistonSettings(${this.id})">
                    <input type="button" value="🗑" id="piston-${this.id}-remove" onclick="removePiston(${this.id})">
                </div>
            </div>
        `;
    }

    press() {
        console.log(`Piston (${this.id}, ${this.name})`)

        this.controlledElements.forEach(ce => {
            ce.press();
        });
    }

    setId(val) {
        this.setName(`Piston ${val}`);
        document.getElementById(`piston-${this.id}-name`).id = `piston-${val}-name`;
        document.getElementById(`piston-${this.id}-button`).id = `piston-${val}-button`;        
        document.getElementById(`piston-${this.id}`).id = `piston-${val}`;

        document.getElementById(`piston-${this.id}-settings`).onclick = () => pistonSettings(val);
        document.getElementById(`piston-${this.id}-remove`).onclick = () => removePiston(val);

        document.getElementById(`piston-${this.id}-settings`).id = `piston-${val}-settings`;
        document.getElementById(`piston-${this.id}-remove`).id = `piston-${val}-remove`;

        this.id = val;
    }

    setName(val) {
        this.name = val;
        document.getElementById(`piston-${this.id}-name`).innerText = val;
    }
}

function addPiston() {
    let nextId = pistons.length;
    let toAdd = new piston(nextId, `Piston ${nextId}`);

    pistons.push(toAdd);
    rightContainerContent.appendChild(toAdd.htmlElement);
}

function removePiston(id) {
    if(window.confirm(`Czy na pewno usunąć piston ${id}?`)) {
        elem = pistons.splice(id, 1)[0];
        rightContainerContent.removeChild(elem.htmlElement);

        for (let i = id; i < pistons.length; i++) {
            current = pistons[i];
            current.setId(i);
        }
    }
}

function pistonSettings(id) {
    window.alert(`Tutaj byłoby okienko ustawień pistonu ${id}`);
}

// =============
// == SECTION ==
// =============

class section {
    id;
    name;
    voices;
    htmlElement;

    constructor(id, name, voices=[]) {
        this.id = id;
        this.name = name;
        this.voices = voices;

        this.htmlElement = document.createElement('div');
        this.htmlElement.id = `section-${id}-container`;
        this.htmlElement.className = "";
        this.htmlElement.innerHTML = `
            <div>
                <span id="section-${this.id}-name">${this.name}</span>
                <input type="button" value="+" id="section-${this.id}-button">
            </div>
            
            <div>
                <input type="button" value="⚙" id="section-${this.id}-settings" onclick="sectionSettings(${this.id})">
                <input type="button" value="🗑" id="section-${this.id}-remove" onclick="removeSection(${this.id})">
            </div>

            <div id="section-${id}-voices-container" class="border-margin-padding">

            </div>
        `;        
    }

    assignVoice(voice) {
        const voicesContainer = document.getElementById(`section-${this.id}-voices-container`);
        voicesContainer.appendChild(voice.htmlElement);
    }

    deassignVoice(voice) {
        const voicesContainer = document.getElementById(`section-${this.id}-voices-container`);
        voicesContainer.removeChild(voice.htmlElement);
    }

    press(keyNumber) {
        console.log(`Sekcja: (${this.id}, ${this.name}), klawisz ${keyNumber}`);

        voices.forEach(v => {
            v.play();
        });
    }

    setId(val) {
        this.setName(`Sekcja ${val}`);
        document.getElementById(`section-${this.id}-container`).id = `section-${val}-container`;
        document.getElementById(`section-${this.id}-name`).id = `section-${val}-name`;
        document.getElementById(`section-${this.id}-button`).id = `section-${val}-button`;
        document.getElementById(`section-${this.id}-voices-container`).id = `section-${val}-voices-container`;

        document.getElementById(`section-${this.id}-remove`).onclick = () => removeSection(val);
        document.getElementById(`section-${this.id}-settings`).onclick = () => sectionSettings(val);

        document.getElementById(`section-${this.id}-remove`).id = `section-${val}-remove`;
        document.getElementById(`section-${this.id}-settings`).id = `section-${val}-settings`;        

        this.id = val;
    }

    setName(val) {
        this.name = val;
        document.getElementById(`section-${this.id}-name`).innerText = val;
    }
}

function addSection() {
    let nextId = sections.length;
    let toAdd = new section(nextId, `Sekcja ${nextId}`);

    sections.push(toAdd);
    leftContainerContent.appendChild(toAdd.htmlElement);
    document.getElementById(`section-${toAdd.id}-button`).addEventListener('click', () => addVoice(toAdd));
}

function removeSection(id) {
    if(window.confirm(`Czy na pewno usunąć sekcję ${id}?`)) {
        let voicesToRemove = [];

        voices.forEach(v => {
            if (v.section.id === id) {
                voicesToRemove.push(v);
            }
        });

        voicesToRemove.forEach(v => {
            removeVoice(v.id, conf=true);
        });

        elem = sections.splice(id, 1)[0];
        leftContainerContent.removeChild(elem.htmlElement);

        for (let i = id; i < sections.length; i++) {
            current = sections[i];
            current.setId(i);
        }
    }
}

function sectionSettings(id) {
    window.alert(`Tutaj byłoby okienko ustawień sekcji ${id}`);
}

// ================
// == EXPRESSION ==
// ================

class expression {
    id;
    keyboard;

    constructor(id, keyboard) {
        this.id = id;
        this.keyboard = keyboard;
    }

    setId(val) {

    }
}

function addExpression() {

}

function removeExpression(id) {
    window.alert(`Czy na pewno usunąć pedał ekspresji ${id}?`);
}

function expressionSettings(id) {
    window.alert(`Tutaj byłoby okienko ustawień pedału ekspresji ${id}`);
}

// ===========
// == VOICE ==
// ===========

class voice {
    id;
    name;
    section;

    constructor(id, name, section) {
        this.id = id;
        this.name = name;
        this.section = section;

        this.htmlElement = document.createElement('div');
        this.htmlElement.id = `voice-${id}-container`;
        this.htmlElement.className = "border-margin-padding";
        this.htmlElement.innerHTML = `
            <div>
                <span id="voice-${id}-name">Głos ${id}</span>
            </div>

            <div>
                <input type="button" value="⚙" id="voice-${this.id}-settings" onclick="voiceSettings(${this.id})">
                <input type="button" value="🗑" id="voice-${this.id}-remove" onclick="removeVoice(${this.id})">
            </div>
        `;
    }

    play() {
        console.log(`Głos (${this.id}, ${this.name})`)
    }

    setId(val) {        
        this.setName(`Głos ${val}`);
        document.getElementById(`voice-${this.id}-name`).id = `voice-${val}-name`;
        document.getElementById(`voice-${this.id}-container`).id = `voice-${val}-container`;

        document.getElementById(`voice-${this.id}-settings`).onclick = () => voiceSettings(val);
        document.getElementById(`voice-${this.id}-remove`).onclick = () => removeVoice(val);

        document.getElementById(`voice-${this.id}-remove`).id = `voice-${val}-remove`;
        document.getElementById(`voice-${this.id}-settings`).id = `voice-${val}-settings`;

        this.id = val;
    }

    setName(val) {
        this.name = val;
        document.getElementById(`voice-${this.id}-name`).innerText = val;
    }

    setSection(val) {
        sectId = this.section.id;
        const cont = document.getElementById(`section-${sectId}-voices-container`);
        cont.removeChild(this.htmlElement);

        this.section = val;
        this.section.appendChild(this.htmlElement);        
    }
}

function addVoice(sect) {
    let nextId = voices.length;
    let toAdd = new voice(nextId, `Głos ${nextId}`, sect);

    sect.assignVoice(toAdd);
    voices.push(toAdd);
}

function removeVoice(id, conf=false) {
    if(conf || window.confirm(`Czy na pewno usunąć głos ${id}?`)) {
        elem = voices.splice(id, 1)[0];
        elem.section.deassignVoice(elem);

        for (let i = id; i < voices.length; i++) {
            current = voices[i];
            current.setId(i);
        }
    }
}

function voiceSettings(id) {
    window.alert(`Tutaj byłoby okienko ustawień głosu ${id}`);
}

window.addEventListener('DOMContentLoaded', () => {
    loadInstrument();
})