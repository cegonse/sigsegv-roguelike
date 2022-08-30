const path = require("path")
const fs = require("fs")
const libpng = require("pngjs").PNG.sync
const buffer = require("./buffer")

const loadImage = (filePath) => {
  try {
    const data = fs.readFileSync(filePath);
    return libpng.read(data);
  } catch (e) {
    return {
      error: e.message
    }
  }
}

const textureFormats = {
  rgba32: 0x00,
  rgb24: 0x01
}

const toBinary = (textureId, image, format, data) => {
  const textureIdLengthBuffer = buffer.uint32leBuffer(textureId.length)
  const textureIdBuffer = Buffer.from(textureId, 'ascii')
  const textureFormatBuffer = buffer.uint8Buffer(textureFormats[format])
  const textureWidthBuffer = buffer.uint32leBuffer(image.width)
  const textureHeightBuffer = buffer.uint32leBuffer(image.height)
  const textureDataBuffer = Buffer.from([...data])
  const textureSizeBuffer = buffer.uint32leBuffer(textureDataBuffer.byteLength)

  return Buffer.concat([
    textureIdLengthBuffer,
    textureIdBuffer,
    textureFormatBuffer,
    textureWidthBuffer,
    textureHeightBuffer,
    textureSizeBuffer,
    textureDataBuffer
  ])
}

const kCOLORTYPE_RGB = 2
const kCOLORTYPE_RGBA = 6

const readFormat = (image) => {
  if (image.colorType === kCOLORTYPE_RGB && image.depth === 8 && image.bpp === 3) {
    return "rgb24"
  }

  if (image.colorType === kCOLORTYPE_RGBA && image.depth === 8 && image.bpp === 4) {
    return "rgba32"
  }

  return "unsupported"
}

const prepareData = (data, format) => {
  if (format === "rgba32") {
    return data
  }

  const finalBuffer = []

  for (var i=0; i<data.length; i+=4) {
    finalBuffer.push(data.slice(i, i+3))
  }

  return Buffer.concat(finalBuffer)
}

const packTexture = (filePath) => {
  const image = loadImage(filePath);
  if (image.error) {
    return {
      error: image.error
    }
  }

  const textureId = path.basename(filePath).split('.')[0];
  const format = readFormat(image);

  if (format === "unsupported") {
    return {
      error: `Unsupported format (${image.colorType})`
    }
  }

  return {
    metadata: {
      id: textureId,
      width: image.width,
      height: image.height,
      format
    },
    data: prepareData(image.data, format),
    binary: toBinary(textureId, image, format, prepareData(image.data, format))
  }
}

module.exports = {
  packTexture
};
