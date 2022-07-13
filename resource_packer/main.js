const fs = require("fs")

const directory = process.argv[2]

if (!directory) {
  console.log("No resource pack")
  process.exit(1);
}

const textures = [];

fs.readdir(`${process.cwd()}/${directory}`, (_, files) => {
  files.forEach(file => {
    if (file.includes(".png")) {
      textures.push(file);
    }
  })

  processResourceFiles();
})

// For all resources
// XX XX XX XX Num resources (little endian 32 bit unsigned int)
//
// For each texture resource
// XX XX XX XX Texture id length (little endian 32 bit unsigned int)
// [XX] Texture ID in ASCII
// XX XX XX XX Texture path length (little endian 32 bit unsigned int)
// [XX] Texture path in ASCII

function processResourceFiles() {
  const chunks = [];
  const textureChunks = [];

  textures.forEach((texture) => {
    const textureId = texture.split('.')[0];

    const pathLengthBuffer = uint32leBuffer(textureId.length)
    const idLengthBuffer = uint32leBuffer(texture.length)
    const idBuffer = Buffer.from(textureId, 'ascii')
    const pathBuffer = Buffer.from(texture)

    textureChunks.push(Buffer.concat([
      idLengthBuffer,
      idBuffer,
      pathLengthBuffer,
      pathBuffer
    ]))
  })

  chunks.push(uint32leBuffer(textureChunks.length))

  textureChunks.forEach((chunk) => chunks.push(chunk))

  console.log(`Processed ${textureChunks.length} resources`)

  const fullBuffer = Buffer.concat(chunks)
  fs.writeFileSync("resources.pack", fullBuffer)
}

function uint32leBuffer(num) {
  const buffer = Buffer.alloc(4)
  buffer.writeUInt32LE(num)
  return buffer
}
