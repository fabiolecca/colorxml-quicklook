#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>
#include <QuickLook/QuickLook.h>

/* -----------------------------------------------------------------------------
   Generate a preview for file

   This function's job is to create preview for designated file
   ----------------------------------------------------------------------------- */

OSStatus GeneratePreviewForURL(void *thisInterface, QLPreviewRequestRef preview, CFURLRef url, CFStringRef contentTypeUTI, CFDictionaryRef options)
{
printf("GeneratePreviewForURL");

	
//	CFStringRef resultString;
    CFStringRef percorso;
    CFStringRef output;

   CFURLRef sourceURL;
   CFURLRef bundleURL;
   CFURLRef resourceURL;
   
   CFStringRef bundlePath;
   CFStringRef resourcePath;
   
  CFDataRef data;
	CFBundleRef requestedBundle;

  
  time_t tempo;
  
 SInt32    errorCode;
 //CFDataRef xmlData;
 
 int resultcode;
 
    char stringona[10240];
    char tempfile[10240];
    char tempfileURL[10240];
	
		tempo = time(NULL);
		
		printf("%ld\n\n\n", tempo);
		
    percorso = CFURLCopyFileSystemPath(url,kCFURLPOSIXPathStyle);
	
		  //percorso = CFURLGetString(url);
	
	printf("************");
	printf("************");
	printf("************");
	printf("************");
	printf("************");
	
	
	
	requestedBundle = CFBundleGetBundleWithIdentifier(
        CFSTR("it.araneum.qlgenerator.xml") );
		
	 
	 bundleURL = CFBundleCopyBundleURL(requestedBundle);
	 bundlePath = CFURLCopyFileSystemPath(bundleURL,kCFURLPOSIXPathStyle);
	 
	 resourceURL = CFBundleCopyResourcesDirectoryURL(requestedBundle);
	 resourcePath = CFURLCopyFileSystemPath(resourceURL,kCFURLPOSIXPathStyle);
	 
	 
	 printf("BUNDLEEEEEEEEEE  %s/%s",  CFStringGetCStringPtr(bundlePath, 0), CFStringGetCStringPtr(resourcePath, 0));
	
	 
 //  resultString = CFStringCreateWithCString(0, "<html>CAZZO C'HAI DA GUARDARE?</html>", 0);



//CFShow( resultString);
//	CFShow( percorso);
	
//CFShow( resultString);
	
//  resultString = CFStringCreateWithCString(0, percorso, 0);
	sprintf(tempfile, "/tmp/it.araneum.qlgenerator.xml.%ld.html", tempo);
	sprintf(tempfileURL, "file://localhost/tmp/it.araneum.qlgenerator.xml.%ld.html", tempo);
	
	 sprintf(stringona, "xsltproc --nonet  --novalid \"/%s/%s/xmlverbatimwrapper.xsl\" \"%s\" > %s",   CFStringGetCStringPtr(bundlePath, 0), CFStringGetCStringPtr(resourcePath, 0),CFStringGetCStringPtr(percorso, 0),tempfile);
	printf("\n%s\n", stringona);		
	resultcode = system(stringona);

	printf("\nEXITCODE: %d\n", resultcode);
	
//	percorso =  CFStringCreateWithFileSystemRepresentation(0, CFStringGetCStringPtr(percorso, 0));
	
 //   data = CFStringCreateExternalRepresentation(NULL, percorso, CFStringGetSystemEncoding(), '?');


   output = CFStringCreateWithCString(0, tempfileURL, 0);
	
	
	sourceURL = CFURLCreateWithString (NULL, // allocator
	(CFStringRef)output, // url string
	NULL); // base url


if (resultcode==0)
{
 CFURLCreateDataAndPropertiesFromResource
     (NULL, // allocator
     sourceURL, &data,
     NULL, NULL, // properties
     &errorCode);
}	 
else
{
CFURLCreateDataAndPropertiesFromResource
     (NULL, // allocator
     url, &data,
     NULL, NULL, // properties
     &errorCode);
}

	 printf("ERROR: %d\n", errorCode);
	
   if (data != NULL) {
    //    printf ("zzzzzzz%.*s\n\n", (int)CFDataGetLength(data), CFDataGetBytePtr(data));
           }
	
if (resultcode==0)
		QLPreviewRequestSetDataRepresentation(preview, data, kUTTypeHTML, NULL);
else
		QLPreviewRequestSetDataRepresentation(preview, data, kUTTypePlainText, NULL);


	sprintf(stringona, "rm %s",tempfile);
	printf("\n%s\n", stringona);		
	resultcode = system(stringona);

	CFRelease(data);
    CFRelease(requestedBundle);
	
	
	CFRelease(percorso);
    CFRelease(output);

   CFRelease(sourceURL);
   CFRelease(bundleURL);
   CFRelease(resourceURL);
   
   CFRelease(bundlePath);
   CFRelease(resourcePath);
   
 
    return noErr;
}

void CancelPreviewGeneration(void* thisInterface, QLPreviewRequestRef preview)
{
printf("CancelPreviewGeneration");
    // implement only if supported
}
