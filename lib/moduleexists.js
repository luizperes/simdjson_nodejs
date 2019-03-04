function moduleExists(modulePath) {
    try {
      return !!require.resolve(modulePath)
    } catch (e) {
      return false
    }
  }
  module.exports = moduleExists;