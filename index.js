const MyReadableStream = require('./myreadable')

var myStream = new MyReadableStream();

const stream = require('stream')
const Readable = stream.Readable;

var Transform = stream.Transform

class StreamTamer extends Transform {
	constructor(options) {
    super(options)
  }

  _transform(data, enc, cb)  {
    setTimeout(() => {
      cb(null, data)
    }, 7)
    //cb(null, data)
  }
}

myStream.pipe(new StreamTamer()).pipe(process.stdout);