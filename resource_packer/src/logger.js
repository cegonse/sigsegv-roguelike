const log = (message) => {
  if (process.env["NODE_ENV"] !== "test") {
    console.log(`[${new Date().toISOString()}] ${message}`)
  }
}

module.exports = {
  log
}
