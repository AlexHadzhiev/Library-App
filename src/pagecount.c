#include <mupdf/fitz.h>
#include <stdlib.h>
#include <stdio.h>

#include "include/pagecount.h"

int
pagecount ( char * filename )
{
	fz_context * ctx;
	fz_document * doc;
	int page_count;
	
	ctx = fz_new_context ( NULL , NULL , FZ_STORE_UNLIMITED );
	if ( !ctx )
	{
		fprintf ( stderr , "Failed to create mupdf context\n" );
		return -1;
	}

	fz_try ( ctx )
	{
		fz_register_document_handlers ( ctx );
	}
	fz_catch ( ctx )
	{
		fprintf ( stderr , "Failed to register document handlers: %s\n" , fz_caught_message ( ctx ) );
		fz_drop_context ( ctx );
		return -1;
	}

	fz_try ( ctx )
	{
		doc = fz_open_document ( ctx , filename );
	}
	fz_catch ( ctx )
	{
		fprintf ( stderr , "Failed to open document: %s\n" , fz_caught_message ( ctx ) );
		fz_drop_context ( ctx );
		return -1;
	}

	fz_try ( ctx )
	{
		page_count = fz_count_pages ( ctx , doc );
	}
	fz_catch ( ctx )
	{
		fprintf ( stderr , "Failed to count the number of pages: %s\n" , fz_caught_message ( ctx ) );
		fz_drop_document ( ctx , doc );
		fz_drop_context ( ctx );
		return -1;
	}

	fz_drop_document ( ctx , doc );
	fz_drop_context ( ctx );

	return page_count;
}
