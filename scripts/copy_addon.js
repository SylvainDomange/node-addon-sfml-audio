const fs = require('fs');
const path = require('path');

const name = 'sfml_audio';

fs.copyFileSync(
    path.join(__dirname, `../build/Release/${name}.node`),
    path.join(__dirname, `../js/${name}.node`)
    );

fs.copyFileSync(
    path.join(__dirname, `../src/${name}.d.ts`),
    path.join(__dirname, `../js/${name}.d.ts`)
    );
