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
/*
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
*/
});

var express    = require('express')
var bodyParser = require('body-parser')

var app  = express()
var port = process.env.PORT || 8000

// mongoose.connection.close();

app.use(bodyParser.json({limit: '1mb'}));


var testR = express.Router();

testR.get('/:id', function (req, res) {
    Test.findOne({where: {id: req.params.id}})
    .then(function (tests) {
        res.json(tests);
    })
    .catch(function (err) {
        console.error(err);
        res.status(400);
        res.error(err);
    });
});

testR.get('/', function (req, res) {
    Test.findAll()
    .then(function (tests) {
        res.json(tests);
    })
    .catch(function (err) {
        console.error(err);
        res.status(400);
        res.error(err);
    });
});

app.use('/test', testR);

var apiR = express.Router();

apiR.use(bodyParser.json());
apiR.post('/answerTest', function (req, res) {
    const id = req.body.test_id;
    const answer = req.body.test_answer;
    Test.findOne({where: {id: id}})
    .then(function (test) {
        if (!test) return res.status(400).json({result: false, error: "cannot find test"});
        const check = test.answer === answer;
        console.log("your answer: '" + answer + "'");
        console.log("true answer: '" + test.answer + "'");
        if (check) console.log("Ok");
        else console.log("Nop");

        res.json({result: check});
    })
    .catch(function (err) {
        console.error(err);
        res.status(400);
        res.error(err);
    });
});

apiR.get('/randomTest', function (req, res) {
    Test.count().then(function (count) {
        Test.findOne({where: {id: (Math.random()*count + 1)|0}})
        .then(function (tests) {
            res.json(tests);
        })
        .catch(function (err) {
            console.error(err);
            res.status(400);
            res.error(err);
        });
    });
});

app.use('/api', apiR);

app.listen(port, function () {
  console.log('server listening on port:', port)
})
