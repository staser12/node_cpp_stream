const stream = require('stream')

const Readable = stream.Readable;

const bufferExample = require('./build/Release/buffer_example');

class MyReadableStream extends Readable {
  constructor(options) {
    super(options)
  }

  _read(n) {
    //this.push('aaa\n')

    //this.push(null)

    bufferExample.getBuffAsync((err, buff) => {
      if (!err) {
        this.push(buff)
      } else {
        console.error(err)
      }
    })

  }
}

module.exports = MyReadableStream
