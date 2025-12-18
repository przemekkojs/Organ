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

        console.log(`Klawiatura ${id}: ${keyNumber}`);
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
    nextId = keyboards.length;    
    toAdd = new keyboard(nextId);

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

}

function addPiston() {

}

function removePiston(id) {
    window.alert(`Czy na pewno usunąć piston ${id}?`);
}

function pistonSettings(id) {
    window.alert(`Tutaj byłoby okienko ustawień pistonu ${id}`);
}

// =============
// == SECTION ==
// =============

class section {

}

function addSection() {

}

function removeSection(id) {
    window.alert(`Czy na pewno usunąć sekcję ${id}?`);
}

function sectionSettings(id) {
    window.alert(`Tutaj byłoby okienko ustawień sekcji ${id}`);
}

// ================
// == EXPRESSION ==
// ================

class expression {

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

}

function addVoice() {

}

function removeVoice(id) {
    window.alert(`Czy na pewno usunąć głos ${id}?`);
}

function voiceSettings(id) {
    window.alert(`Tutaj byłoby okienko ustawień głosu ${id}`);
}

window.addEventListener('DOMContentLoaded', () => {
    loadInstrument();
    addSection();
    addVoice(sections[0]);
    addPiston();
    addKeyboard();
    addExpression();
})