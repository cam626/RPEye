const assert = require('assert');
const path = require('path');

const apis = require(path.join(__dirname, '..', '..', 'api'));

/** Tests that getDocIds yeilds documents */
/*
function testGetDocIds() {
  apis.getDocIds('', (resp) => {
    assert(resp.docs);
    assert(resp.docs.length >= 0);
  });
    
  apis.getDocIds('test test' (resp) {
    assert(resp.docs);
    assert(resp.docs.length >= 0);
  });

  apis.getDocIds('test', (resp) => {
    assert(resp.docs);
    assert(resp.docs.length >= 0);
  });
}
*/

/*
function testGetPages() {
  apis.getPages([], (resp) => {
    assert(resp.length == 0);
  });
  apis.getPages([-1], (resp) => {
    assert(resp.length == 0);
  });
  apis.getPages([5,8,9], (resp) =>{
    assert(resp.length == 0);
  });
}
*/
//module.exports = {testGetDocIds, testGetPages};
