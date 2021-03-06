
https://docs.mongodb.org/getting-started/python/    This guide provides instructions to get you started using MongoDB.
https://docs.mongodb.org/ecosystem/drivers/python/  This is an overview of the available tools for using Python with MongoDB.

http://api.mongodb.org/python/current/index.html     
http://api.mongodb.org/python/current/tutorial.html
http://www.cnblogs.com/libingql/archive/2011/06/15/2081545.html PyMongo基本使用

API
  bson 每 BSON (Binary JSON) Encoding and Decoding
    binary 每 Tools for representing binary data to be stored in MongoDB
    regex 每 Tools for representing MongoDB regular expressions
    code 每 Tools for representing JavaScript code
    codec_options 每 Tools for specifying BSON codec options
    dbref 每 Tools for manipulating DBRefs (references to documents stored in MongoDB)
    errors 每 Exceptions raised by the bson package
    int64 每 Tools for representing BSON int64
    json_util 每 Tools for using Python＊s json module with BSON documents
    max_key 每 Representation for the MongoDB internal MaxKey type
    min_key 每 Representation for the MongoDB internal MinKey type
    objectid 每 Tools for working with MongoDB ObjectIds
    son 每 Tools for working with SON, an ordered mapping
    timestamp 每 Tools for representing MongoDB internal Timestamps
    tz_util 每 Utilities for dealing with timezones in Python
  pymongo 每 Python driver for MongoDB
    database 每 Database level operations
    collection 每 Collection level operations
    command_cursor 每 Tools for iterating over MongoDB command results
    cursor 每 Tools for iterating over MongoDB query results
    bulk 每 The bulk write operations interface
    errors 每 Exceptions raised by the pymongo package
    message 每 Tools for creating messages to be sent to MongoDB
    monitoring 每 Tools for monitoring driver events.
    mongo_client 每 Tools for connecting to MongoDB
    mongo_replica_set_client 每 Tools for connecting to a MongoDB replica set
    operations 每 Operation class definitions
    pool 每 Pool module for use with a MongoDB client.
    read_preferences 每 Utilities for choosing which member of a replica set to read from.
    results 每 Result class definitions
    son_manipulator 每 Manipulators that can edit SON documents as they are saved or retrieved
    cursor_manager 每 Managers to handle when cursors are killed after being closed
    uri_parser 每 Tools to parse and validate a MongoDB URI
    write_concern 每 Tools for specifying write concern
  gridfs 每 Tools for working with GridFS
    errors 每 Exceptions raised by the gridfs package
    grid_file 每 Tools for representing files stored in GridFS

-------------------------------------------------------------------------------

--> tutorial

 http://api.mongodb.org/python/current/tutorial.html	
	
 -->--> Making a Connection with MongoClient
  The first step when working with PyMongo is to create a MongoClient to the  running 
  mongod instance. Doing so is easy:

  >>> from pymongo import MongoClient
  >>> client = MongoClient() # connect on the default host and port
  >>> client = MongoClient('localhost', 27017) # specify the host and port explicitly
  >>> client = MongoClient('mongodb://localhost:27017/') #use the MongoDB URI format

 -->--> Getting a Database
  A single instance of MongoDB can support multiple independent databases. When work-
  ing with PyMongo you access databases using attribute style access on MongoClient -
  instances: 

  >>> db = client.test_database  # test_database is database name
  # If your database name is such that using attribute style access won't work ( like  
  # test-database), you can use dictionary style access instead:
  >>> db = client['test-database']

 -->--> Getting a Collection
  A collection is a group of documents stored in MongoDB, and can be thought of as r-
  oughly the equivalent of a table in a relational database. Getting a collection  in 
  PyMongo works the same as getting a database:

  >>> collection = db.test_collection # test_collection is collection name
  # or (using dictionary style access):
  >>> collection = db['test-collection']
  # An important note about collections (and databases) in MongoDB is that they are -
  # created lazily - none of the above commands have actually performed any operatio-
  # ns on the MongoDB server. Collections and databases are created when the first d-
  # ocument is inserted into them.
  >>>

 -->--> Documents
  Data in MongoDB is represented (and stored) using JSON-style documents. In  PyMongo 
  we use dictionaries to represent documents. As an example, the following dictionary 
  might be used to represent a blog post:
  >>> import datetime
  >>> post = {"author": "Mike",
  ...         "text": "My first blog post!",
  ...         "tags": ["mongodb", "python", "pymongo"],
  ...         "date": datetime.datetime.utcnow()}
  Note that documents can contain native Python types (like datetime.datetime instan-
  ces) which will be automatically converted to and from the appropriate BSON types.

 -->--> Inserting a Document
  To insert a document into a collection we can use the insert_one() method: 
  >>> posts = db.posts # posts is collection name
  >>> post_id = posts.insert_one(post).inserted_id
  >>> post_id
  ObjectId('...')

  When a document is inserted a special key, "_id", is automatically added if the do-
  cument doesn't already contain an "_id" key. The value of "_id" must be unique acr-
  oss the collection. insert_one() returns an instance of InsertOneResult. For more -
  information on "_id", see the documentation on _id. After inserting the first docu-
  ment, the posts collection has actually been created on the server. We can verify -
  this by listing all of the collections in our database: 
  >>> db.collection_names(include_system_collections=False)
  [u'posts']

 -->--> Getting a Single Document With find_one() 
  The most basic type of query that can be performed in MongoDB is find_one(). This -
  method returns a single document matching a query (or None if there are no matches)
  . It is useful when you know there is only one matching document, or are only inte-
  rested in the first match. Here we use find_one() to get the first document from t-
  he posts collection:
  
  >>> posts.find_one()
  {u'date': datetime.datetime(...), u'text': u'My first blog post!', u'_id': ObjectId\
   ('...'), u'author': u'Mike', u'tags': [u'mongodb', u'python', u'pymongo']}

  The result is a dictionary matching the one that we inserted previously. Note The -
  returned document contains an "_id", which was automatically added on insert.     -
  find_one() also supports querying on specific elements that the resulting  document 
  must match. To limit our results to a document with author ※Mike§ we do:
  
  >>> posts.find_one({"author": "Mike"})
  {u'date': datetime.datetime(...), u'text': u'My first blog post!', u'_id': ObjectId\
   ('...'), u'author': u'Mike', u'tags': [u'mongodb', u'python', u'pymongo']}

  If we try with a different author, like ※Eliot§, we'll get no result:
  
  >>> posts.find_one({"author": "Eliot"})
  >>>

  
  

-------------------------------------------------------------------------------------  
  
--> Insert Data with PyMongo
 https://docs.mongodb.org/getting-started/python/insert/

 -->--> Overview
  You can use the insert_one() method and the insert_many() method to add documents -
  to a collection in MongoDB. If you attempt to add documents to a collection that d-
  oes not exist, MongoDB will create the collection for you.

 -->--> Prerequisites
  From a Python Shell or IDLE, use MongoClient to connect to the running mongod inst-
  ance, and switch to the test database.

  from pymongo import MongoClient
  client = MongoClient()
  db = client.test
  
 -->--> Insert a Document
  Insert a document into a collection named @restaurants. The operation will create -
  the collection if the collection does not currently exist.

  from datetime import datetime
  result = db.restaurants.insert_one(
    {
        "address": {
            "street": "2 Avenue",
            "zipcode": "10075",
            "building": "1480",
            "coord": [-73.9557413, 40.7720266]
        },
        "borough": "Manhattan",
        "cuisine": "Italian",
        "grades": [
            {
                "date": datetime.strptime("2014-10-01", "%Y-%m-%d"),
                "grade": "A",
                "score": 11
            },
            {
                "date": datetime.strptime("2014-01-16", "%Y-%m-%d"),
                "grade": "B",
                "score": 17
            }
        ],
        "name": "Vella",
        "restaurant_id": "41704620"
    }
  )
  
  The operation returns an InsertOneResult object, which includes an attribute      -
  inserted_id that contains the _id of the inserted document. Access the  inserted_id 
  attribute:
  
  >>> result.inserted_id

  The ObjectId of your inserted document will differ from the one shown.

  >>> ObjectId("54c1478ec2341ddf130f62b7")

  If the document passed to the insert_one() method does not contain the _id field, -
  MongoClient automatically adds the field to the document and sets the field’s value 
  to a generated ObjectId.  

--> Find or Query Data with PyMongo
 https://docs.mongodb.org/getting-started/python/query/

 -->--> Overview
  You can use the find() method to issue a query to retrieve data from a collection -
  in MongoDB. All queries in MongoDB have the scope of a single collection.

  Queries can return all documents in a collection or only the documents that match -
  a specified filter or criteria. You can specify the filter or criteria in a docume-
  nt and pass as a parameter to the find() method.

  The find() method returns query results in a cursor, which is an iterable object t-
  hat yields documents.

 -->--> Prerequisites
  The examples in this section use the restaurants collection in the test database. -
  For instructions on populating the collection with the sample dataset, see Import -
  Example Dataset.

  From a Python Shell or IDLE, use MongoClient to connect to the running mongod inst-
  ance, and switch to the test database.

  > from pymongo import MongoClient
  
  > client = MongoClient()
  > db = client.test

 -->--> Query for All Documents in a Collection
  To return all documents in a collection, call the find() method without a  criteria 
  document. For example, the following operation queries for all documents in the re-
  staurants collection.

  > cursor = db.restaurants.find()
  
  Iterate the cursor and print the documents.

  > for document in cursor:
  >    print(document)
  
 The result set contains all documents in the restaurants collection.

 -->--> Specify Equality Conditions
  The query condition for an equality match on a field has the following form:

  { <field1>: <value1>, <field2>: <value2>, ... }
 
  If the <field> is in an embedded document or an array, use dot notation to access -
  the field.

  1 Query by a Top Level Field
  The following operation finds documents whose borough field equals "Manhattan".

  > cursor = db.restaurants.find({"borough": "Manhattan"})
 
  Iterate the cursor and print the matching documents.

  > for document in cursor:
  >    print(document)
  
  The result set includes only the matching documents.

  2 Query by a Field in an Embedded Document
  To specify a condition on a field within an embedded document, use the dot notatio-
  n. Dot notation requires quotes around the whole dotted field name. The following -
  operation specifies an equality condition on the zipcode field in the address embe-
  dded document.

  > cursor = db.restaurants.find({"address.zipcode": "10075"})
  
  Iterate the cursor and print the matching documents.

  > for document in cursor:
  >   print(document)
 
  The result set includes only the matching documents.

  For more information on querying on fields within an embedded document, see Embedd-
  ed Documents.

  3 Query by a Field in an Array
  The grades array contains embedded documents as its elements. To specify a conditi-
  on on a field in these documents, use the dot notation. Dot notation requires quot-
  es around the whole dotted field name. The following queries for documents whose g-
  rades array contains an embedded document with a field grade equal to "B".

  > cursor = db.restaurants.find({"grades.grade": "B"})
  
  Iterate the cursor and print the matching documents.

  > for document in cursor:
  >    print(document)
 
  The result set includes only the matching documents.

  For more information on querying on arrays, such as specifying multiple  conditions 
  on array elements, see Arrays and $elemMatch.

 -->--> Specify Conditions with Operators
  MongoDB provides operators to specify query conditions, such as comparison operato-
  rs. Although there are some exceptions, such as the $or and $and conditional opera-
  tors, query conditions using operators generally have the following form:

  { <field1>: { <operator1>: <value1> } }
  
  For a complete list of the operators, see query operators.

  1 Greater Than Operator ($gt)
  Query for documents whose grades array contains an embedded document with a field -
  score greater than 30.

  > cursor = db.restaurants.find({"grades.score": {"$gt": 30}})
 
  Iterate the cursor and print the matching documents.

  > for document in cursor:
  >    print(document)
  
  The result set includes only the matching documents.

  2 Less Than Operator ($lt)
  Query for documents whose grades array contains an embedded document with a field -
  score less than 10.

  > cursor = db.restaurants.find({"grades.score": {"$lt": 10}})
 
  Iterate the cursor and print the matching documents.

  > for document in cursor:
  >    print(document)
 
  The result set includes only the matching documents.

 -->--> Combine Conditions
  You can combine multiple query conditions in logical conjunction (AND) and  logical 
  disjunctions (OR).

  1 Logical AND
  You can specify a logical conjunction (AND) for a list of query conditions by sepa-
  rating the conditions with a comma in the conditions document.

  > cursor = db.restaurants.find({"cuisine": "Italian", "address.zipcode": "10075"})
 
  Iterate the cursor and print the matching documents.

  > for document in cursor:
  >    print(document)
  
  The result set includes only the documents that matched all specified criteria.

  2 Logical OR
  You can specify a logical disjunction (OR) for a list of query conditions by  using 
  the $or query operator.

  > cursor = db.restaurants.find(
      {"$or": [{"cuisine": "Italian"}, {"address.zipcode": "10075"}]})
  Iterate the cursor and print the matching documents.

  > for document in cursor:
  >    print(document)
 
  The result set includes only the documents that match either conditions.

 -->--> Sort Query Results
  To specify an order for the result set, append the sort() method to the query. Pass 
  to sort() method a document which contains the field(s) to sort by and the corresp-
  onding sort type, e.g. pymongo.ASCENDING for ascending and pymongo.DESCENDING for -
  descending.

  To sort by multiple keys, pass a list of keys and sort type pairs. For example, th-
  e following operation returns all documents in the restaurants collection, sorted -
  first by the borough field in ascending order, and then, within each borough, by t-
  he "address.zipcode" field in ascending order:

  > import pymongo
  > cursor = db.restaurants.find().sort([
      ("borough", pymongo.ASCENDING),
      ("address.zipcode", pymongo.DESCENDING)
    ])
 
  Iterate the cursor and print the matching documents.

  > for document in cursor:
  >    print(document)
 
  The operation returns the results sorted in the specified order.

--> Update Data with PyMongo
 https://docs.mongodb.org/getting-started/python/update/
 
 -->--> Overview
  You can use the update_one() and the update_many() methods to update documents of a 
  collection. The update_one() method updates a single document. Use update_many() to 
  update all documents that match the criteria. The methods accept the following par-
  ameters:
  
  1 a filter document to match the documents to update,
  2 an update document to specify the modification to perform, and
  3 an optional upsert parameter.
  
  To specify the update filter, use the same structure and syntax as the query condi-
  tions. See Find or Query Data with PyMongo for an introduction to query conditions.

  You cannot update the _id field.

 -->--> Prerequisites
  The examples in this section use the restaurants collection in the test database. -
  For instructions on populating the collection with the sample dataset, see Import -
  Example Dataset.

  From a Python Shell or IDLE, use MongoClient to connect to the running mongod inst-
  ance, and switch to the test database.
  >>> from pymongo import MongoClient
  >>> client = MongoClient()
  >>> db = client.test
  
 -->--> Update Specific Fields
  To change a field value, MongoDB provides update operators, such as $set to  modify 
  values. Some update operators, such as $set, will create the field if the field do-
  es not exist. See the individual update operators reference.
  
  update operators: https://docs.mongodb.org/manual/reference/operator/update/

  -->-->--> Update Top-Level Fields
   The following operation updates the first document with name equal to "Juni", usi-
   ng the $set operator to update the cuisine field and the $currentDate operator  to 
   update the lastModified field with the current date.
  
   result = db.restaurants.update_one(
     {"name": "Juni"},
     {
         "$set": {
             "cuisine": "American (New)"
         },
         "$currentDate": {"lastModified": True}
     }
   )

   The operation returns a UpdateResult object that reports the count of documents m-
   atched and modified.

   To see the number of documents that matched the filter condition, access the     - 
   matched_count attribute of the returned UpdateResult object.

   > result.matched_count
   The matched_count is :
   > 1

  -->-->--> Update an Embedded Field
   To update a field within an embedded document, use the dot notation. When using t-
   he dot notation, enclose the whole dotted field name in quotes. The following upd-
   ates the street field in the embedded address document.

   result = db.restaurants.update_one(
     {"restaurant_id": "41156888"},
     {"$set": {"address.street": "East 31st Street"}}
   )
  
   The operation returns a UpdateResult object that reports the count of documents m-
   atched and modified.

   To see the number of documents that matched the filter condition, access the     -
   matched_count attribute of the returned UpdateResult object.

   > result.matched_count
   The matched_count is:
   > 1

  -->-->--> Update Multiple Documents
   The update_one() method updates a single document. To update multiple documents, -
   use the update_many() method. The following operation updates all documents that -
   have address.zipcode field equal to "10016" and cuisine field equal to "Other", s-
   etting the cuisine field to "Category To Be Determined" and the lastModified field  
   to the current date.

   result = db.restaurants.update_many(
     {"address.zipcode": "10016", "cuisine": "Other"},
     {
         "$set": {"cuisine": "Category To Be Determined"},
         "$currentDate": {"lastModified": True}
     }
   )
  
   The operation returns a UpdateResult object that reports the count of documents m-
   atched and modified.

   To see the number of documents that matched the filter condition, access the     -
   matched_count attribute of the returned UpdateResult object.

   > result.matched_count
   The matched_count is:
   > 20

 -->--> Replace a Document
  To replace the entire document except for the _id field, pass an entirely new docu-
  ment as the second argument to the update() method. The replacement document can h-
  ave different fields from the original document. In the replacement document, you -
  can omit the _id field since the _id field is immutable. If you do include the  _id 
  field, it must be the same value as the existing value.

  IMPORTANT
  After the update, the document only contains the field or fields in the replacement 
  document.

  After the following update, the modified document will only contain the _id  field, 
  name field, the address field. i.e. the document will not contain the             -
  restaurant_id, cuisine, grades, and the borough fields.

  result = db.restaurants.replace_one(
    {"restaurant_id": "41704620"},
    {
        "name": "Vella 2",
        "address": {
            "coord": [-73.9557413, 40.7720266],
            "building": "1480",
            "street": "2 Avenue",
            "zipcode": "10075"
        }
    }
  )

  The replace_one operation returns an UpdateResult object which contains the  status 
  of the operation.

  To see the number of documents that matched the filter condition, access the      -
  matched_count attribute of the returned UpdateResult object.

  result.matched_count
  The matched_count is:
  1

 -->--> Additional Information
  If no document matches the update condition, the default behavior of the update me-
  thod is to do nothing. By specifying the upsert option to true, the update operati-
  on either updates matching document(s) or inserts a new document if no matching do-
  cument exists. In the PyMongo documentation, see update_one() and update_many().

  In MongoDB, write operations are atomic on the level of a single document. If a si-
  ngle update operation modifies multiple documents of a collection, the operation c-
  an interleave with other write operations on that collection.In the MongoDB Manual, 
  see Atomicity.

  For all available update operators, see the Update Operators reference page in  the 
  MongoDB Manual.

--> Remove Data with PyMongo
 -->--> Overview
  You can use the delete_one() method and the delete_many() method to remove documen-
  ts from a collection. The method takes a conditions document that determines the d-
  ocuments to remove.

  To specify a remove condition, use the same structure and syntax as the query cond-
  itions.See Find or Query Data with PyMongo for an introduction to query conditions.

 -->--> Prerequisites
  The examples in this section use the restaurants collection in the test database. -
  For instructions on populating the collection with the sample dataset, see Import -
  Example Dataset.

  From a Python Shell or IDLE, use MongoClient to connect to the running mongod inst-
  ance, and switch to the test database.

  from pymongo import MongoClient

  client = MongoClient()
  db = client.test
  
 -->--> Procedures
  -->-->--> Remove All Documents That Match a Condition
   The following operation removes all documents that match the specified condition.

   > result = db.restaurants.delete_many({"borough": "Manhattan"})
   
   The operation returns a DeleteResult which reports the number of documents remove-
   d.

   To see the number of documents deleted, access the deleted_count attribute of  the 
   returned DeleteResult object.

   > result.deleted_count
   The deleted_count is:
   > 10259

   If you have inserted or updated documents, such as specified in the Insert Data or 
   Update Data sections of the Getting Started guide, your count may differ.

  -->-->--> Remove All Documents
   To remove all documents from a collection, pass an empty conditions document {} to 
   the delete_many() method.

   > result = db.restaurants.delete_many({})

   The operation returns a DeleteResult which reports the number of documents removed.

   To see the number of documents deleted, access the deleted_count attribute of  the 
   returned DeleteResult object.

   > result.deleted_count
   The deleted_count is:
   > 15100
  
   If you have inserted or updated documents, such as specified in the Insert Data or 
   Update Data sections of the Getting Started guide, your count may differ.

  -->-->--> Drop a Collection
   The remove all operation only removes the documents from the collection. The coll-
   ection itself, as well as any indexes for the collection, remain. To remove all d-
   ocuments from a collection, it may be more efficient to drop the entire collectio-
   n, including the indexes, and then recreate the collection and rebuild the indexe-
   s. Use the drop() method to drop a collection, including any indexes.

   > db.restaurants.drop()

 -->--> Additional Information
  In the PyMongo documentation, see delete_one(), delete_many() and drop().

  In MongoDB, write operations are atomic on the level of a single document. If a si-
  ngle remove operation removes multiple documents from a collection, the operation -
  can interleave with other write operations on that collection. In the MongoDB Manu-
  al, see Atomicity.

