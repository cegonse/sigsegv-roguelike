const jsonObject = require('../src/json-object')

describe('Packing JSON object files', () => {
  // XX XX XX XX Total length (LE UINT32)
  // XX XX XX XX Object ID length (LE UINT32)
  // [XX]        Non-null terminated ID in ASCII
  // XX XX XX XX Number of entries (LE UINT32)
  // For each string entry
  // 01 00 00 00 Entry type (STRING)
  // XX XX XX XX Key length (LE UINT32)
  // [XX]        Non-null terminated key string in ASCII
  // XX XX XX XX Value length (LE UINT32)
  // [XX]        Non-null terminated value string in ASCII
  it('may include one string', () => {
    const json = {
      hello: 'world'
    }
    const buffer = jsonObject.encode(json, 'object')

    expect([...buffer]).toEqual([
      0x20, 0x00, 0x00, 0x00,
      0x01, 0x00, 0x00, 0x00,
      0x06, 0x00, 0x00, 0x00,
      0x6F, 0x62, 0x6A, 0x65, 0x63, 0x74,
      0x01, 0x00, 0x00, 0x00,
      0x05, 0x00, 0x00, 0x00,
      0x68, 0x65, 0x6C, 0x6C, 0x6F,
      0x05, 0x00, 0x00, 0x00,
      0x77, 0x6F, 0x72, 0x6C, 0x64
    ])
  })

  it('may include many strings', () => {
    const json = {
      first: 'hello',
      second: 'bye'
    }
    const buffer = jsonObject.encode(json, 'object')

    expect([...buffer]).toEqual([
      0x35, 0x00, 0x00, 0x00,
      0x02, 0x00, 0x00, 0x00,
      0x06, 0x00, 0x00, 0x00,
      0x6F, 0x62, 0x6A, 0x65, 0x63, 0x74,

      0x01, 0x00, 0x00, 0x00,
      0x05, 0x00, 0x00, 0x00,
      0x66, 0x69, 0x72, 0x73, 0x74,
      0x05, 0x00, 0x00, 0x00,
      0x68, 0x65, 0x6C, 0x6C, 0x6F,

      0x01, 0x00, 0x00, 0x00,
      0x06, 0x00, 0x00, 0x00,
      0x73, 0x65, 0x63, 0x6F, 0x6E, 0x64,
      0x03, 0x00, 0x00, 0x00,
      0x62, 0x79, 0x65
    ])
  })

  // For each number entry
  // 02 00 00 00 Entry type (NUMBER)
  // XX XX XX XX Key length (LE UINT32)
  // [XX]        Non-null terminated key string in ASCII
  // XX XX XX XX Value (LE Float)
  it('may include numeric values', () => {
    const json = {
      hello: 1.5
    }
    const buffer = jsonObject.encode(json, 'object')

    expect([...buffer]).toEqual([
      0x1B, 0x00, 0x00, 0x00,
      0x01, 0x00, 0x00, 0x00,
      0x06, 0x00, 0x00, 0x00,
      0x6F, 0x62, 0x6A, 0x65, 0x63, 0x74,

      0x02, 0x00, 0x00, 0x00,
      0x05, 0x00, 0x00, 0x00,
      0x68, 0x65, 0x6C, 0x6C, 0x6F,
      0x00, 0x00, 0xC0, 0x3F
    ])
  })

  it('may mix numeric and string values', () => {
    const json = {
      hello: 2.1,
      world: 'bye'
    }
    const buffer = jsonObject.encode(json, 'object')

    expect([...buffer]).toEqual([
      0x2F, 0x00, 0x00, 0x00,
      0x02, 0x00, 0x00, 0x00,
      0x06, 0x00, 0x00, 0x00,
      0x6F, 0x62, 0x6A, 0x65, 0x63, 0x74,

      0x02, 0x00, 0x00, 0x00,
      0x05, 0x00, 0x00, 0x00,
      0x68, 0x65, 0x6C, 0x6C, 0x6F,
      0x66, 0x66, 0x06, 0x40,

      0x01, 0x00, 0x00, 0x00,
      0x05, 0x00, 0x00, 0x00,
      0x77, 0x6F, 0x72, 0x6C, 0x64,
      0x03, 0x00, 0x00, 0x00,
      0x62, 0x79, 0x65
    ])
  })

  // For each boolean entry
  // 03 00 00 00 Entry type (BOOLEAN)
  // XX XX XX XX Key length (LE UINT32)
  // [XX]        Non-null terminated key string in ASCII
  // XX Value (8 bit unsigned integer)
  it('may include boolean values', () => {
    const json = {
      false: false,
      true: true
    }
    const buffer = jsonObject.encode(json, 'object')

    expect([...buffer]).toEqual([
      0x25, 0x00, 0x00, 0x00,
      0x02, 0x00, 0x00, 0x00,
      0x06, 0x00, 0x00, 0x00,
      0x6F, 0x62, 0x6A, 0x65, 0x63, 0x74,

      0x03, 0x00, 0x00, 0x00,
      0x05, 0x00, 0x00, 0x00,
      0x66, 0x61, 0x6C, 0x73, 0x65,
      0x00,

      0x03, 0x00, 0x00, 0x00,
      0x04, 0x00, 0x00, 0x00,
      0x74, 0x72, 0x75, 0x65,
      0x01
    ])
  })

  // For each object entry
  // 04 00 00 00 Entry type (OBJECT)
  // XX XX XX XX Key length (LE UINT32)
  // [XX]        Non-null terminated key string in ASCII
  // XX XX XX XX Number of entries (LE UINT32)
  // XX XX XX XX Object length (LE UINT32)
  // Same attributes as first level objects
  it('may include object values', () => {
    const json = {
      one: 2.1,
      two: false,
      three: {
        yes: 'no',
        num: 2.1
      }
    }
    const buffer = jsonObject.encode(json, 'object')

    expect([...buffer]).toEqual([
      0x5A, 0x00, 0x00, 0x00,
      0x03, 0x00, 0x00, 0x00,
      0x06, 0x00, 0x00, 0x00,
      0x6F, 0x62, 0x6A, 0x65, 0x63, 0x74,

      0x02, 0x00, 0x00, 0x00,
      0x03, 0x00, 0x00, 0x00,
      0x6F, 0x6E, 0x65,
      0x66, 0x66, 0x06, 0x40,

      0x03, 0x00, 0x00, 0x00,
      0x03, 0x00, 0x00, 0x00,
      0x74, 0x77, 0x6F,
      0x00,

      0x04, 0x00, 0x00, 0x00,
      0x05, 0x00, 0x00, 0x00,
      0x74, 0x68, 0x72, 0x65, 0x65,
      0x02, 0x00, 0x00, 0x00,
      0x20, 0x00, 0x00, 0x00,

      0x01, 0x00, 0x00, 0x00,
      0x03, 0x00, 0x00, 0x00,
      0x79, 0x65, 0x73,
      0x02, 0x00, 0x00, 0x00,
      0x6E, 0x6F,

      0x02, 0x00, 0x00, 0x00,
      0x03, 0x00, 0x00, 0x00,
      0x6E, 0x75, 0x6D,
      0x66, 0x66, 0x06, 0x40,
    ])
  })

  // For each array entry
  // 05 00 00 00 Entry type (ARRAY)
  // XX XX XX XX Key length (LE UINT32)
  // [XX]        Non-null terminated key string in ASCII
  // XX XX XX XX Array item type
  // XX XX XX XX Num items (LE UINT32)
  // For numbers
  // XX XX XX XX Value (LE Float) in each entry
  // For strings
  // XX XX XX XX Value length (LE UINT32)
  // [XX]        Non-null terminated value string in ASCII
  // For booleans
  // XX Value (8 bit unsigned integer)
  it('may include array values', () => {
    const json = {
      numbers: [2.1, 1.5],
      strings: ['a', 'b'],
      booleans: [false, true]
    }
    const buffer = jsonObject.encode(json, 'object')

    expect([...buffer]).toEqual([
      0x64, 0x00, 0x00, 0x00,
      0x03, 0x00, 0x00, 0x00,
      0x06, 0x00, 0x00, 0x00,
      0x6F, 0x62, 0x6A, 0x65, 0x63, 0x74,

      0x05, 0x00, 0x00, 0x00,
      0x07, 0x00, 0x00, 0x00,
      0x6E, 0x75, 0x6D, 0x62, 0x65, 0x72, 0x73,
      0x02, 0x00, 0x00, 0x00,
      0x02, 0x00, 0x00, 0x00,
      0x66, 0x66, 0x06, 0x40,
      0x00, 0x00, 0xC0, 0x3F,

      0x05, 0x00, 0x00, 0x00,
      0x07, 0x00, 0x00, 0x00,
      0x73, 0x74, 0x72, 0x69, 0x6E, 0x67, 0x73,
      0x01, 0x00, 0x00, 0x00,
      0x02, 0x00, 0x00, 0x00,
      0x01, 0x00, 0x00, 0x00,
      0x61,
      0x01, 0x00, 0x00, 0x00,
      0x62,

      0x05, 0x00, 0x00, 0x00,
      0x08, 0x00, 0x00, 0x00,
      0x62, 0x6F, 0x6F, 0x6C, 0x65, 0x61, 0x6E, 0x73,
      0x03, 0x00, 0x00, 0x00,
      0x02, 0x00, 0x00, 0x00,
      0x00,
      0x01
    ])
  })
})
