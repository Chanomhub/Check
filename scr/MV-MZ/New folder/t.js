const fs = require('fs');
const translator = require('@parvineyvazov/json-translator');

// Function to read file asynchronously
function readFileAsync(path) {
  return new Promise((resolve, reject) => {
    fs.readFile(path, 'utf8', (err, data) => {
      if (err) {
        reject(err);
      } else {
        resolve(data);
      }
    });
  });
}

// Function to translate JSON objects
async function translateFiles(filePaths) {
  try {
    for (const file of filePaths) {
      const jsonContent = await readFileAsync(file);
      const translatedJson = translator.translate(jsonContent);
      console.log(`Translation for ${file}:`);
      console.log(translatedJson);
    }
  } catch (error) {
    console.error('Error occurred:', error);
  }
}

// Read file_paths.json
readFileAsync('file_paths.json')
  .then(data => {
    const fileData = JSON.parse(data);
    const filePaths = fileData.files.map(filePath => filePath.replace(/\//g, '\\'));
    return filePaths;
  })
  .then(translateFiles)
  .catch(error => {
    console.error('Error reading file_paths.json:', error);
  });
