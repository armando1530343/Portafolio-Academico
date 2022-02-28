package edu.upv.poo.util;

/**
 * Represents an exception thrown while calling a Web Service.
 * @author Luis Roberto Flores
 */
public class WebServiceException
    extends Exception {
    
    public WebServiceException(String message) {
        super(message);
    }
    
    public WebServiceException(String message, Throwable cause) {
        super(message, cause);
    }
}
