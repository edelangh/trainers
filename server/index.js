var Sequelize = require('sequelize');
var sequelize = new Sequelize('database', 'username', 'password', {
  dialect: 'sqlite',
  storage: 'db.sqlite',
});

var Profile = sequelize.define('Profile', {
  id: {
    type: Sequelize.INTEGER,
    autoIncrement: true,
    primaryKey: true
  },
  username: Sequelize.STRING,
});

var TestType = sequelize.define('TestType', {
  id: {
    type: Sequelize.INTEGER,
    autoIncrement: true,
    primaryKey: true
  },
  name: Sequelize.STRING,
});

var Test = sequelize.define('Test', {
  id: {
    type: Sequelize.INTEGER,
    autoIncrement: true,
    primaryKey: true
  },
  // TestType
  query: Sequelize.STRING,
  answer: Sequelize.STRING,
  hardness: Sequelize.INTEGER
});
Test.belongsTo(TestType, {foreignKey: {name: 'TestTypeId', allowNull: false}})

var Answer = sequelize.define('Answer', {
  id: {
    type: Sequelize.INTEGER,
    autoIncrement: true,
    primaryKey: true
  },
  // ProfileId
  // TestId
  answer: Sequelize.STRING,
  result: Sequelize.BOOLEAN,
});
Answer.belongsTo(Profile, {foreignKey: 'ProfileId'});
Answer.belongsTo(Test, {foreignKey: 'TestId'});

sequelize.sync().then(function() {
  return TestType.create({
    name: 'strict'
  }).then(function (testType) {

  return Test.create({
    query: 'test ?',
    answer: 'ok !',
    hardness: '90',
    TestTypeId: testType.id
  });
}).then(function(test) {
  console.log(test.get({
    plain: true
  }));
});
});

/*
var express    = require('express')
var bodyParser = require('body-parser')

var app  = express()
var port = process.env.PORT || 8000

var mongoose = require('mongoose');
var Schema = require('mongoose').Schema;

mongoose.connect('mongodb://localhost/bbfs', function(err) {
  if (err) { throw err; }
});

var logSchema = new mongoose.Schema({
  id: Schema.ObjectId,
  path: String,
  inode: Number,
  user_name: String,
  mac: String,
  action: String,
  timestamp: { type : Date, default : Date.now }
});

var Log = mongoose.model('Log', logSchema);

// Si on a utilisÃÂÃÂÃÂÃÂÃÂÃÂÃÂÃÂ© mongoose.connect()
// mongoose.connection.close();

app.use(bodyParser.json({limit: '20mb'}));

app.put('/data', function (req, res) {
  const logs = req.body.logs

  console.log('data:', logs)
  logs.map((log) => {
    new Log(log).save()
  });
  res.end()
})

app.listen(port, function () {
  console.log('server listening on port:', port)
})

*/
