const path = require("path")
const libpng = require("node-libpng")
const buffer = require("./buffer")

const loadImage = (filePath) => {
  try {
    return libpng.readPngFileSync(filePath);
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

const toBinary = (textureId, image, format) => {
  const textureIdLengthBuffer = buffer.uint32leBuffer(textureId.length)
  const textureIdBuffer = Buffer.from(textureId, 'ascii')
  const textureFormatBuffer = buffer.uint8Buffer(textureFormats[format])
  const textureWidthBuffer = buffer.uint32leBuffer(image.width)
  const textureHeightBuffer = buffer.uint32leBuffer(image.height)
  const textureDataBuffer = Buffer.from([...image.data])
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

const readFormat = (image) => {
  if (image.colorType === "rgb" && image.bitDepth === 8 && image.channels === 3) {
    return "rgb24"
  }

  if (image.colorType === "rgba" && image.bitDepth === 8 && image.channels === 4) {
    return "rgba32"
  }

  return "unsupported"
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
    data: image.data,
    binary: toBinary(textureId, image, format)
  }
}

module.exports = {
  packTexture
};
