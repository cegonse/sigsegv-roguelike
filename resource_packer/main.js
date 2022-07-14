const packer = require("./src/packer")

const directory = process.argv[2]

if (!directory) {
  console.log("No resource pack")
  process.exit(1);
}

packer.readFilesFromPath(directory)
