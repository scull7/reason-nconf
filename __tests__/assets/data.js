/*
 * data.js: Simple data fixture for configuration test.
 *
 * (C) 2011, Charlie Robbins and the Contributors.
 *
 */

module.exports = {
  isNull: null,
  literal: 'bazz',
  arr: ['one', 2, true, { value: 'foo' }],
  obj: {
    host: 'localhost',
    port: 5984,
    array: ['one', 2, true, { foo: 'bar' }],
    auth: {
      username: 'admin',
      password: 'password'
    }
  }
};
