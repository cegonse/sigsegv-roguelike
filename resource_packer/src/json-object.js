const buffer = require("./buffer")

const OBJECT_TYPES = {
  "string": buffer.uint32leBuffer(1),
  "number": buffer.uint32leBuffer(2)
}

const encode = (object) => {
  const keys = Object.keys(object)
  const items = []

  keys.forEach(key => {
    const value = object[key]
    const keyBuffer = Buffer.from(key, 'ascii')

    if (typeof(value) === "string") {
      const valueBuffer = Buffer.from(value, 'ascii')

      items.push(Buffer.concat([
        OBJECT_TYPES.string,
        buffer.uint32leBuffer(key.length),
        keyBuffer,
        buffer.uint32leBuffer(value.length),
        valueBuffer
      ]))
    } else if (typeof(value) === "number") {
      const valueBuffer = buffer.floatLeBuffer(value)

      items.push(Buffer.concat([
        OBJECT_TYPES.number,
        buffer.uint32leBuffer(key.length),
        keyBuffer,
        valueBuffer
      ]))
    }
  })
  const itemsBuffer = Buffer.concat(items)

  return Buffer.concat([
    buffer.uint32leBuffer(items.length),
    buffer.uint32leBuffer(itemsBuffer.length),
    itemsBuffer
  ])
}

module.exports = {
  encode
}
