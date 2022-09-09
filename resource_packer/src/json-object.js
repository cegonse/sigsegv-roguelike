const buffer = require("./buffer")

const OBJECT_TYPES = {
  "string": buffer.uint32leBuffer(1),
  "number": buffer.uint32leBuffer(2),
  "boolean": buffer.uint32leBuffer(3),
  "object": buffer.uint32leBuffer(4)
}

const encodeObject = (object, items) => {
  const keys = Object.keys(object)

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
    } else if (typeof(value) === "boolean") {
      const valueBuffer = buffer.uint8Buffer(value)

      items.push(Buffer.concat([
        OBJECT_TYPES.boolean,
        buffer.uint32leBuffer(key.length),
        keyBuffer,
        valueBuffer
      ]))
    } else if (
      typeof(value) === "object" &&
      !Array.isArray(value)
    ) {
      const objectItems = []
      encodeObject(value, objectItems)
      const objectBuffer = Buffer.concat(objectItems)
      items.push(Buffer.concat([
        OBJECT_TYPES.object,
        buffer.uint32leBuffer(key.length),
        keyBuffer,
        buffer.uint32leBuffer(objectItems.length),
        buffer.uint32leBuffer(objectBuffer.length),
        ...objectItems
      ]))
    }
  })
}

const encode = (object) => {
  const items = []
  encodeObject(object, items)
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
