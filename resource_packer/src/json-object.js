const buffer = require('./buffer')
const logger = require('./logger')

const OBJECT_TYPES = {
  'string': buffer.uint32leBuffer(1),
  'number': buffer.uint32leBuffer(2),
  'boolean': buffer.uint32leBuffer(3),
  'object': buffer.uint32leBuffer(4),
  'array': buffer.uint32leBuffer(5)
}

const valueType = (value) => {
  if (typeof(value) === 'string') {
    return 'string'
  } else if (typeof(value) === 'number') {
    return 'number'
  } else if (typeof(value) === 'boolean') {
    return 'boolean'
  } else if (
    typeof(value) === 'object' &&
    !Array.isArray(value)
  ) {
    return 'object'
  } else if (
    typeof(value) === 'object' &&
    Array.isArray(value)
  ) {
    return 'array'
  }
}

const encodeObject = (object, items) => {
  const keys = Object.keys(object)

  keys.forEach(key => {
    const value = object[key]
    const keyBuffer = Buffer.from(key, 'ascii')
    const type = valueType(value)

    if (type === 'string') {
      const valueBuffer = Buffer.from(value, 'ascii')

      items.push(Buffer.concat([
        OBJECT_TYPES.string,
        buffer.uint32leBuffer(key.length),
        keyBuffer,
        buffer.uint32leBuffer(value.length),
        valueBuffer
      ]))
    } else if (type === 'number') {
      const valueBuffer = buffer.floatLeBuffer(value)

      items.push(Buffer.concat([
        OBJECT_TYPES.number,
        buffer.uint32leBuffer(key.length),
        keyBuffer,
        valueBuffer
      ]))
    } else if (type === 'boolean') {
      const valueBuffer = buffer.uint8Buffer(value)

      items.push(Buffer.concat([
        OBJECT_TYPES.boolean,
        buffer.uint32leBuffer(key.length),
        keyBuffer,
        valueBuffer
      ]))
    } else if (type === 'object') {
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
    } else if (type === 'array') {
      const arrayType = valueType(value[0])

      if (!arrayType) {
        logger.log('>> Encoding empty arrays not supported')
        return
      }
      
      if (arrayType === "object") {
        logger.log('>> Encoding array of objects not supported')
        return
      }

      if (arrayType === "array") {
        logger.log('>> Encoding array of arrays not supported')
        return
      }

      const arrayItems = value.map((x) => {
        if (arrayType === 'string') {
          return Buffer.concat([
            buffer.uint32leBuffer(x.length),
            Buffer.from(x, 'ascii')
          ])
        } else if (arrayType === 'number') {
          return buffer.floatLeBuffer(x)
        } else if (arrayType === 'boolean') {
          return buffer.uint8Buffer(x)
        }
      })

      items.push(Buffer.concat([
        OBJECT_TYPES.array,
        buffer.uint32leBuffer(key.length),
        keyBuffer,
        OBJECT_TYPES[arrayType],
        buffer.uint32leBuffer(value.length),
        ...arrayItems
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
