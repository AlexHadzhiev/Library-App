#include <mupdf/fitz.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	char *input;
	fz_context *ctx;
	fz_document *doc; argv[1];
	int page_count;
	
	input = argv[1];
	
	ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);
	if(!ctx)
	{
		fprintf(stderr, "Failed to create mupdf context\n");
		return EXIT_FAILURE;
	}
	
	fz_try(ctx)
		fz_register_document_handlers(ctx);
	fz_catch(ctx)
	{
		fprintf(stderr, "Failed to register document handlers: %s\n", fz_caught_message(ctx));
		fz_drop_context(ctx);
		return EXIT_FAILURE;
	}
	
	fz_try(ctx)
		doc = fz_open_document(ctx, input);
	fz_catch(ctx)
	{
		fprintf(stderr, "Failed to open document: %s\n", fz_caught_message(ctx));
		fz_drop_context(ctx);
		return EXIT_FAILURE;
	}
	
	fz_try(ctx)
		page_count = fz_count_pages(ctx, doc);
	fz_catch(ctx)
	{
		fprintf(stderr, "Failed to count number of pages: %s\n", fz_caught_message(ctx));
		fz_drop_document(ctx, doc);
		fz_drop_context(ctx);
		return EXIT_FAILURE;
	}
	
	printf("%d\n", page_count);
}
