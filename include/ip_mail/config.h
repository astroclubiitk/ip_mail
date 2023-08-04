#include <iostream>

const std::string EMAIL_ID = "your-email-id@gmail.com";             // Email account from which mail will be sent
const std::string EMAIL_PASSWORD = "<insert app password here>";    // Authentication string for the above email ID
const std::string DEST_EMAIL = "astroclub@iitk.ac.in";              // Target of destination email account
const int SLEEP_TIMEOUT = 10;                                       // Duration for which to wait for ngrok tunneling to be active