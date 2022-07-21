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

module.exports = {
  uint32leBuffer,
  uint8Buffer
}
