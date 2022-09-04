const ieee754 = require("ieee754")

const uint32leBuffer = (num) => {
  const buffer = Buffer.alloc(4)
  buffer.writeUInt32LE(num)
  return buffer
}

const uint8Buffer = (num) => {
  const buffer = Buffer.alloc(1);
  buffer.writeUInt8(num);
  return buffer;
}

const floatLeBuffer = (num) => {
  const buffer = Buffer.alloc(4);
  ieee754.write(buffer, num, 0, true, 23, 4)
  return buffer;
}


module.exports = {
  uint32leBuffer,
  uint8Buffer,
  floatLeBuffer
}
