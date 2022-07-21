const fs = require("fs")
const texturePacker = require("./textures")
const buffer = require("./buffer")

const log = (message) => {
  if (process.env["NODE_ENV"] !== "test") {
    console.log(message)
  }
}

const readFilesFromPath = (directory, packName) => {
  const textures = [];

  fs.readdir(`${process.cwd()}/${directory}`, (_, files) => {
    files.forEach(file => {
      if (file.includes(".png")) {
        textures.push(`${directory}/${file}`)
      }
    })

    const result = buildResourcePack(textures)
    log(`Processed ${result.numResources} resources`)

    fs.writeFileSync(`${process.cwd()}/${packName}.pack`, result.buffer)
  })
}


const chunksSize = (chunks) => {
  let size = 0;
  chunks.forEach((chunk) => size += chunk.byteLength);
  return size;
}

const buildResourcePack = (textures) => {
  const chunks = []
  const textureChunks = []

  const magicBuffer = Buffer.from('SIGSEGV', 'ascii')
  const bomBuffer = buffer.uint32leBuffer(0x12345678)

  textures.forEach((texture) => {
    const textureData = texturePacker.packTexture(texture)
    log(`- Packing ${texture} (${textureData.metadata.width}x${textureData.metadata.height})`)
    textureChunks.push(textureData.binary)
  })

  chunks.push(buffer.uint32leBuffer(textureChunks.length))
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
    buffer.uint32leBuffer(totalSize),
    Buffer.concat(chunks)
  ])

  return {
    buffer: fullBuffer,
    numResources: textures.length,
    textures
  }
}

module.exports = {
  buildResourcePack,
  readFilesFromPath
}
