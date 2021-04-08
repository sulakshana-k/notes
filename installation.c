https://linuxize.com/post/how-to-install-visual-studio-code-on-ubuntu-18-04/

// For generating Express applications.
sudo apt install node-express-generator


// For generating an express project in a non-empty directory:
express -f


// For installing packages written in `package.json`
npm install


// For installing an individual package and writing its name in `package.json`.
npm install --save <package-name>


// For installing `nodemon` globally.
// `nodemon` is used to ensure node/express application compiles on its own every time
// we modify something.
npm install -g nodemon


// Modifying the dir structure and code according to MVC design pattern.

1. Create a directory <blog_server> in the main directory.
2. Move 'routes' and 'views' directory in 'blog_server' directory.

3. In main directory open 'app.js' and find the following line:
	
	'app.set('views', path.join(__dirname, 'views'));'

   and change it to following:

	'app.set('views', path.join(__dirname, 'blog_server', 'views'));'
		
4. In main directory open 'app.js' and find the following line:
 	'var routes = require('./routes/index');'
	'var users  = require('./routes/users');'

   and change it to the following:
 	'var routes = require('./blog_server/routes/index');'
	'var users  = require('./blog_server/routes/users');'
		

5. Separating Router API and Controller code:

	In 'blog_server/routes/' ---> 'index.js'
		
		var router = express.Router 

		router.get('/', function(req, res) 
				{
				   res.render('index', {title: 'Express'})	
				}
			  )


	Here '/' is the URL which will be put by the user in browser.
	'router' looks for URL in this 'get' function.

	Here 'function(req, res) 
	      {
	         res.render('index', {title: 'Express'})	
	      }
	     '

	     is the Controller function.	

	/* 'render' function takes the html file's name and JavaScript object
	 * containing data for HTML to use.
	 * HTML file's path has already been specified in 'app.js' in main directory. 
	 */ 


6. Get data from database and write CRUD and REST API for the same:

	6.0 Start MongoDB:
		sudo systemctl start mongod
		sudo systemctl status mongod
		sudo systemctl stop mongod

	6.1 /* MongoDB will talk to Mongoose and Mongoose will talk to Express/Nodejs and 
	     * Express/Nodejs will talk to Angular
	     */
        	npm install --save mongoose

	6.2 // Require 'Mongoose' in 'models/db.js'.
		var obj_mongoose = require('mongoose');		

	    // Require 'models/db.js' in 'app.js'.
		require('./blog_server/models/db');

	    // Form database connection:
	    /* Pass URI to connect function of 'mongoose' in 'models/db.js'.
	     * URI:		
	     * mongodb://username:password@localhost:27027/database_name
	     */

	        obj_mongoose.connect( 'mongodb://localhost/blog_db' )

	
	    /*
	     * Verifying the connection by slot 'connection.on' and various signals like
	     * 'connected', 'error', 'disconnected'.
	     */
		obj_mongoose.connection.on('connected', function()
						        {
							   console.log( 'Mongoose connected!' )
						        })


		obj_mongoose.connection.on('error', function( argError )
						    {
							console.log( 'Mongoose connected!', argError );
						    })


		obj_mongoose.connection.on('disconnected', function()
						           {
							       console.log( 'Mongoose disconnected!' )
						           })



	    /*
	     * Gracefully closing MongoDB connection. 
	     * Shown in the book 'Getting MEAN with Mongo, Express, Angular, and Node'. 
	     */

	https://bezkoder.com/node-js-express-sequelize-mysql/


	// To connect to different databases, use 'createConnection' function of mongoose.

	/*
	 * document: 	Row
	 * collection: 	Collection of Documents.
	 * schema:	Design of a Document.
	 * model:	Model defines the programming interface to a schema.
	 * path:	Individual defined entries of a Schema.


	* In normal RDBMS the schema is maintained by CREATE, DELETE kind of statements.
	* Instead of concept of models, RDBMS has SELECT queries to perform operations on database.

	* Primary key:
	*	In MongoDB, _id is generated automatically for each document and can be treated as a primary key
	*	for each document.


	* String:  Any string, UTF-8 encoded
	* Number:  Mongoose doesn’t support long or double numbers, but it can be extended to do so 
		   using Mongoose plugins; the default support is enough for most cases.

	* Date:    Typically returned from MongoDB as an ISODate object.
	* Boolean: True or false
	* Buffer:  For binary information such as images.
	* Mixed:   Any data type
	* Array:   Can either be an array of the same data type, or an array of nested sub-documents
	* ObjectId:For a unique ID in a path other than _id; typically used to reference
			_id paths in other documents



	
	* RDBMS vs NoSql (MongoDB)
	--- 1. 
	* RDBMS -   The schema is maintained by CREATE, DELETE kind of statements.
	* MongoDB - Mongoose is used to create Schema programaticaly.

	--- 2.
	* RDBMS -   RDBMS has SELECT queries to perform operations on database.
	* MongoDB - Models have to be defined programatically. 
 
	--- 3.
	* RDBMS -   If a field for example 'address' has multiple data like house number, street number,
		    coordinates, country name etc, then in RDBMS this will require a separate table.
	* MongoDB - Here 'address' field will contain an array of data but will be stored as a part of the
		    same collection (table).  		
        */


	// Make Schemas in 'models/locations.js':
	
	var mongoose = require('mongoose');
	var mySchema2 = new mongoose.Schema(
					    {
						days:   String,		// One String
						time:   {type: String, required: true}
						rating: {type: number, required: true, min: 0; max: 5},
						facilities: [String], 	// Array of Strings
						
						otherSchema: [<mySchema1>] // Other schemas can be nested by specifying their names.
						reviews: [<review_schema_name>]
					    }
					  )

	
// Compiling the schema into a model:

/* Command:
 *	mongoose.model(<model_name>, <schema_name>, <collection_name>)

 * <collection_name> is optional. If we do not specify it then a default collection name
 * is chosen based on <model_name> with small first alphabet and an s in the end.
 */


// Filling data in MongoDB

// This will create the said database if it doesn't exist and switch to it.
// use <database_name>

use test

// This is the way to insert data in 'test' database.
// 'locations' is the <collection_name>.

db.locations.save({
		     name: 'DEF'
		     date: '24 Dec 2020',
		     time: '13:55',
		     rating: 5,
		     facilities: ['Hot drinks', 'Food', 'Premium wifi'],
		     otherSchema: [
			  	    {
				      name: 'Sulak',
				      closed: false
				    }
			          ]
	          }
                 )

db.locations.save({
		     name: 'ABC',	
		     date: '26 Dec 2020',
		     time: '12:55',
		     rating: 4,
		     facilities: ['Cold drinks', 'Tea', 'Premium wifi'],
		     otherSchema: [
				     {
				       name: 'Ben',
				       closed: true
				     }
			          ]
	          }
                 )

// Retrieve all the data from a <collection_name>.
// Here 'locations' is the collection name.

db.locations.find()

// Review for each restaurant in a restaurant finder app will be added on the fly.
// Documents need to be updated as follows:

db.<collection_name>.update({<query_to_find_relevant_document>}, {<thing_to_do_when_the_said_document_is_found>})

db.locations.update({name: 'ABC'}, { $push: { reviews: { author: 'myname', rating: 5, review_text: "Nice place!" } } } )


// REST API

/*
 * URLs and parameter names can be same in many URLs. The way to differenciate
 * between them is to check whether they are for POST, DELETE, PUT or GET or some other command.

 * Sub-documents require an additional parameter in the URL.
   Example: http://loc8r.com/api/locations/123/reviews/456

   
   For a HTTP request there has to be a response always with the status code and some data if required.
   Data format for an API request and response can be in JSON or XML format.

 */

// To write the REST API we should have a separate folder:
	app_api/

// and have 3 folders inside it:
	controllers:
	   locations.js  reviews.js

	models:
	   db.js  locations.js

	routes:
	   index.js  locations.js

// Write its require statement in app.js:

	var routesApi = require('./app_api/routes/index');

// And use it in app.js:
	app.use('/api', routesApi)


// Write REST API functions in 'app_api/routes/locations.js'
// REST API functions have to be derived from Router module which is a part of Express.

	var express = require('Express')
	var router = express.Router()

	var ctrlLocations = require('../controllers/locations.js')
	var ctrlReviews   = require('../controllers/reviews.js')
	
	router.post( '/locations', ctrlLocations.locationsCreate)
	router.get ( '/locations', ctrlLocations.locationsListByDistance)
	router.get ( '/locations/:locationid', ctrlLocations.locationsReadOne)
	router.put ( '/locations/:locationid', ctrlLocations.locationsUpateOne)
	router.delete( '/locations/:locationid', ctrlLocations.locationsDeleteOne)

	router.get ( '/locations/:locationid/reviews', ctrlReviews.reviewsReadOne)
	router.post( '/locations/:locationid/reviews', ctrlReviews.reviewsCreate)
	router.put( '/locations/:locationid/reviews:reviewid', ctrlReviews.reviewsUpdateOne)
	router.delete( '/locations/:locationid/reviews:reviewid', ctrlReviews.reviewsDeleteOne)


// Define these controller functions in their respective files with dummy data as responses:

// app_api/controllers/locations.js
module.exports.locationsCreate = function( request, response )
				{
					sendJSONResponse( response, 200, {"status": "success"})
				}

module.exports.locationsListByDistance = function( request, response )
					  {
						sendJSONResponse( response, 200, {"status": "success"})
					  }
...
var sendJSONResponse = function( response, arg_status, content )
				{
					response.status( arg_status)
					response.json( content)
				}

// app_api_controllers/reviews.js

module.exports.reviewsCreate = function( request, response )
				{
				}


module.exports.reviewsReadOne = function( request, response )
				{
				}

// Now get real data by accessing the model which we created in 'app_api/models/locations.js'

// To access the model we need to include 'app_api/models/locations.js' in 
// 'app_api/controllers/locations.js' like this:

	require('../models/locations.js')

	var mongoose = require('mongoose')
	var Loc = mongoose.model( 'Location' )


// Now fetch a record by using _id field of the collection 'locations':

// Apply 'findById' to 'Loc' (model's object), and then apply 'exec' to it:


	Loc.findById( <Id> ).exec( function( error, received_data ) 
				{
				})	


// Put this in the get API's controller function:

	module.exports.locationsReadOne = function( request, response )
					  {
					    // 'locationId' is the parameter name in the API that we've formed above.	
			 		    Loc.findById( request.params.locationId ).exec( function( error, arg_received_data )
									 		    {
								     				sendJSONResponse( response, 
														  200, 
														  arg_received_data )
								   			    }
								                          )
					  }

// Error checking should be put in place as follows:
	if( request.params && request.params.locationId )
	{
	   Loc.findById( request.params.locationId ).exec( function( error, arg_received_data )
							   {
							        if( error )
								   sendJSONResponse( response, 404, error )
								else if( !arg_received_data )
								   sendJSONResponse( response, 404, {"status": "No data"} )
								else 
								   sendJSONResponse( response, 200, arg_received_data )
							   }
	}
	else
	{
	   sendJSONResponse( response, 404, {"status": "No parameters specified"} )
	}



// Repeat the same with 'reviews.js'

module.exports.reviewsReadOne 
		= function( arg_request, arg_response )
  		  {
			// This time we will verify 'reviewId' too. Reviews are a sub-document	
		     if( arg_request.params 
				&& arg_request.params.locationId 
				&& arg_request.params.reviewId )
		     {
			Loc.findById( arg_request.params.locationId )
				// 'select' gives us the exact results instead of dumping everything.
				// Here we want 'name' and 'review' information only.
				.select( 'name, reviews' )
					.exec( function( error, arg_location_data )
					       {
						 var review_l; var our_response_l;	
						 if( !arg_location_data )
						 {
						    sendJSONResponse( arg_response, 404, { "message" : "No data available!"} )
						    return;
						 }
						 else if( error )
						 {
						    sendJSONResponse( arg_response, 404, error )
						    return;
						 }
						      
						  // If there are reviews sub-document in the location data returned by database.
						 if( arg_location_data.reviews && ( arg_location_data.reviews.length > 0 ) )
						 {
						      // Apply '_id' function to	
						    review_l = arg_location_data.reviews.id( arg_request.params.reviewId )
						    if( !review_l )
						    {
							sendJSONResponse( arg_response, 404, {'message': 'Review Id not found!'} )
						    }
						    else
						    {
							 // Send name, id, and review as response JSON object.
							sendJSONResponse( arg_response, 200, { 
												location: 
												  { 
												    name: location.name, 
												    id:   arg_request.params.locationId
												  }, 
												review: review_l 
											     }
									)
						    }
						}
						else
						{
						   sendJSONResponse( arg_response, 404, {"message": "No reviews to show!"})
						}
					       }
					     )

		      
		   }
















































// --------------------------------------------------------- Generic commands ------------------------------------------------------------
// For generating `package.json`
npm init

// For starting an Express application
npm start

// Browser
localhost:3000

