const jsonObject = require("../src/json-object")

describe("Packing JSON object files", () => {
  // XX XX XX XX Number of entries (LE UINT32)
  // XX XX XX XX Total length (LE UINT32)
  // For each string entry
  // 01 00 00 00 Entry type (STRING)
  // XX XX XX XX Key length (LE UINT32)
  // [XX]        Non-null terminated key string in ASCII
  // XX XX XX XX Value length (LE UINT32)
  // [XX]        Non-null terminated value string in ASCII
  it("may include one string", () => {
    const json = JSON.stringify({"hello": "world"})
    const buffer = jsonObject.encode(json)
    
    expect([...buffer]).toEqual([
      0x01, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00,
      0x01, 0x00, 0x00, 0x00,
      0x05, 0x00, 0x00, 0x00
    ])
  })
})
