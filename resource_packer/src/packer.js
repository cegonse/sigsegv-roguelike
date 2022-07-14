const fs = require("fs")
const path = require("path")

function readFilesFromPath(directory) {
  const textures = [];

  fs.readdir(`${process.cwd()}/${directory}`, (_, files) => {
    files.forEach(file => {
      if (file.includes(".png")) {
        textures.push(file)
      }
    })

    const result = buildResourcePack(textures)
    console.log(`Processed ${result.numResources} resources`)
    result.textures.forEach((texture) => console.log(`- ${texture}`))

    fs.writeFileSync(`${process.cwd()}/${directory}.pack`, result.buffer)
  })
}

function buildResourcePack(textures) {
  const chunks = []
  const textureChunks = []

  const magicBuffer = Buffer.from('SIGSEGV', 'ascii')
  const bomBuffer = uint32leBuffer(0x12345678)

  textures.forEach((texture) => {
    const textureId = path.basename(texture).split('.')[0];

    const idLengthBuffer = uint32leBuffer(textureId.length)
    const pathLengthBuffer = uint32leBuffer(texture.length)
    const idBuffer = Buffer.from(textureId, 'ascii')
    const pathBuffer = Buffer.from(texture, 'ascii')

    textureChunks.push(Buffer.concat([
      idLengthBuffer,
      idBuffer,
      pathLengthBuffer,
      pathBuffer
    ]))
  })

  chunks.push(uint32leBuffer(textureChunks.length))
  textureChunks.forEach((chunk) => chunks.push(chunk))

  const totalSize = (
    magicBuffer.byteLength +
    bomBuffer.byteLength +
    chunksSize(chunks) +
    4
  )

  const fullBuffer = Buffer.concat([
    magicBuffer,
    bomBuffer,
    uint32leBuffer(totalSize),
    Buffer.concat(chunks)
  ])

  return {
    buffer: fullBuffer,
    numResources: textures.length,
    textures
  }
}

function chunksSize(chunks) {
  let size = 0;
  chunks.forEach((chunk) => size += chunk.byteLength);
  return size;
}

function uint32leBuffer(num) {
  const buffer = Buffer.alloc(4)
  buffer.writeUInt32LE(num)
  return buffer
}

module.exports = {
  buildResourcePack,
  readFilesFromPath
}
