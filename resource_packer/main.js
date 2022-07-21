const packer = require("./src/packer")

const directory = process.argv[2]
const packName = process.argv[3]

const usage = () => {
  console.log("main.js [resourcesDirectory] [packName]")
}

if (!directory) {
  console.log("No directory specified")
  usage()
  process.exit(1);
}

if (!directory) {
  console.log("No resource pack name specified")
  usage()
  process.exit(1);
}

packer.readFilesFromPath(directory, packName)
