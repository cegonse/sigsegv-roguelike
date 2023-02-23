const fs = require("fs")
const path = require("path")
const texturePacker = require("./textures")
const objectPacker = require("./json-object")
const buffer = require("./buffer")
const logger = require("./logger")

const readFilesFromPath = (directory, packName) => {
  const textures = [];
  const objects = [];

  fs.readdir(`${process.cwd()}/${directory}`, (_, files) => {
    files.forEach(file => {
      if (file.includes(".png")) {
        textures.push(`${directory}/${file}`)
      }

      if (file.includes(".json")) {
        objects.push(`${directory}/${file}`)
      }
    })

    const result = buildResourcePack(
      textures,
      objects
    )
    logger.log(`Processed ${result.numResources} resources`)

    fs.writeFileSync(`${process.cwd()}/${packName}.pack`, result.buffer)
  })
}


const chunksSize = (chunks) => {
  let size = 0;
  chunks.forEach((chunk) => size += chunk.byteLength);
  return size;
}

const parseJsonFile = (p) => JSON.parse(fs.readFileSync(p))

const buildResourcePack = (textures, objects) => {
  const chunks = []
  const textureChunks = []
  const objectChunks = []

  const magicBuffer = Buffer.from('SIGSEGV', 'ascii')

  textures.forEach((texture) => {
    const textureData = texturePacker.packTexture(texture)
    logger.log(`- Packing ${texture} (${textureData.metadata.width}x${textureData.metadata.height} - ${textureData.metadata.format})`)
    textureChunks.push(textureData.binary)
  })

  objects.forEach((obj) => {
    const objectName = path.basename(obj).split('.')[0];
    const objectData = objectPacker.encode(parseJsonFile(obj), objectName);
    logger.log(`- Packing ${obj}`)
    objectChunks.push(objectData)
  })

  chunks.push(buffer.uint32leBuffer(textureChunks.length))
  chunks.push(buffer.uint32leBuffer(objectChunks.length))
  chunks.push(buffer.uint32leBuffer(Buffer.concat(textureChunks).length))
  chunks.push(buffer.uint32leBuffer(Buffer.concat(objectChunks).length))
  textureChunks.forEach((chunk) => chunks.push(chunk))
  objectChunks.forEach((chunk) => chunks.push(chunk))

  const fullBuffer = Buffer.concat([
    magicBuffer,
    buffer.uint32leBuffer(chunksSize(chunks)),
    Buffer.concat(chunks)
  ])

  return {
    buffer: fullBuffer,
    numResources: textures.length + objects.length,
    textures
  }
}

module.exports = {
  buildResourcePack,
  readFilesFromPath
}
