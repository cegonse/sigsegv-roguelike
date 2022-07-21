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
  rgba32: 0x00
}

const toBinary = (textureId, image) => {
  const textureIdLengthBuffer = buffer.uint32leBuffer(textureId.length)
  const textureIdBuffer = Buffer.from(textureId, 'ascii')
  const textureFormatBuffer = buffer.uint8Buffer(textureFormats.rgba32)
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

const packTexture = (filePath) => {
  const image = loadImage(filePath);

  if (image.error) {
    return {
      error: image.error
    }
  }

  const textureId = path.basename(filePath).split('.')[0];

  if (
    image.colorType !== "rgba" &&
    image.bitDepth !== 8 &&
    image.channels !== 4
  ) {
    return {
      error: `Unsupported format (${image.colorType})`
    }
  }

  return {
    metadata: {
      id: textureId,
      width: image.width,
      height: image.height,
      format: "rgba32"
    },
    data: image.data,
    binary: toBinary(textureId, image)
  }
}

module.exports = {
  packTexture
};
