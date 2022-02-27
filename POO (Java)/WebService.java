package edu.upv.poo.util;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLEncoder;
import java.util.Iterator;
import java.util.Map;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

/**
 * Class that provides helping methods to use JSON based web services.
 * @author Luis Roberto Flores
 */
public class WebService {
    
    /**
     * Makes a call to Json Service using the HTTP GET method.
     * @param endpointUrl Service endpoint URL.
     * @param parameters Parameters to be sent to service.
     * @return A JSONObject with the response. 
     * @throws WebServiceException 
     */
    public static JSONObject callJsonServiceWithGet(
            String endpointUrl,
            Map<String, String> parameters) 
            throws WebServiceException {
        JSONObject responseJObj = null;
        if (endpointUrl == null) 
            throw new WebServiceException("endpointUrl cannot be null.");
        endpointUrl = endpointUrl.trim();
        StringBuilder urlSB = new StringBuilder(endpointUrl);
        if (parameters != null) {
            int cantidadParametros = parameters.size();
            if (cantidadParametros > 0) {
                urlSB.append('?');
                Iterator<String> i = parameters.keySet().iterator();
                int pA = 0;
                while(i.hasNext()) {
                    pA++;
                    String paramName = i.next();
                    String paramValue = parameters.get(paramName);
                    try {
                        urlSB.append(URLEncoder.encode(paramName, "UTF-8"));
                        urlSB.append('=');
                        urlSB.append(URLEncoder.encode(paramValue, "UTF-8"));
                        if (pA != cantidadParametros)
                            urlSB.append('&');
                    }
                    catch (java.io.UnsupportedEncodingException ex) {}
                }
            }
        }
        HttpURLConnection httpConn = null;
        URL url = null;
        try {
            try {
                url = new URL(urlSB.toString());
                httpConn = (HttpURLConnection)url.openConnection();
            }
            catch (MalformedURLException ex) {
                throw new Exception("endpointUrl is not valid.");
            }
            catch (IOException ex) {
                throw new Exception("HTTP error while opening the connection.");
            }
            catch (Exception ex) {
                throw new Exception("Undefined error while opening the HTTP connection.");
            }
            httpConn.setDoOutput(false);
            httpConn.setUseCaches(false);
            httpConn.setDoInput(true);
            InputStream inputStream = null;
            try {
                inputStream = httpConn.getInputStream();
            }
            catch (Exception ex){
                throw new Exception("Could not make the request to endpoint.");
            }
            BufferedReader br = new BufferedReader(new InputStreamReader(inputStream));
            String line = "";
            StringBuilder responseSB = new StringBuilder("");
            while ((line = br.readLine()) != null) {
                responseSB.append(line);
            }
            br.close();
            httpConn.disconnect();
            responseSB = new StringBuilder(responseSB.toString().trim());
            int responseLen = responseSB.length();
            if (responseLen > 0) {
                if (responseSB.charAt(0) == '[' && responseSB.charAt(responseLen - 1) == ']') {
                    responseSB.insert(0, "{\"d\": ");
                    responseSB.append(" }");
                }
                JSONParser jsonParser = new JSONParser();
                try {
                    responseJObj = (JSONObject)jsonParser.parse(responseSB.toString());
                }
                catch (ParseException ex) {
                    throw new Exception("Json response could not be parsed.");
                }
            }
        }
        catch (Exception ex) {
            throw new WebServiceException(
                String.format(
                    "Error calling Json Service [%s]. %s", 
                    endpointUrl,
                    ex.getMessage()
                )
            );
        }
        return responseJObj;
    }
    
    /**
     * Makes a call to Json Service using HTTP POST method.
     * @param endpointUrl Service endpoint URL.
     * @param parameters Parameters to be sent.
     * @return A JSONObject with the response.
     * @throws WebServiceException 
     */
    public static JSONObject callJsonServiceWithPost(
            String endpointUrl,
            Map<String, String> parameters)
            throws WebServiceException {
        JSONObject responseJObj = null;
        if (endpointUrl == null) 
            throw new WebServiceException("endpointUrl cannot be null.");
        endpointUrl = endpointUrl.trim();
        if (parameters == null) 
            throw new WebServiceException("parameters cannot be null.");
        if (parameters.isEmpty())
            throw new WebServiceException("parameters cannot be empty.");
        StringBuilder parametersSB = new StringBuilder("");
        if (parameters != null) {
            int cantidadParametros = parameters.size();
            if (cantidadParametros > 0) {
                Iterator<String> i = parameters.keySet().iterator();
                int pA = 0;
                while(i.hasNext()) {
                    pA++;
                    String paramName = i.next();
                    String paramValue = parameters.get(paramName);
                    try {
                        parametersSB.append(URLEncoder.encode(paramName, "UTF-8"));
                        parametersSB.append('=');
                        parametersSB.append(URLEncoder.encode(paramValue, "UTF-8"));
                        if (pA != cantidadParametros)
                            parametersSB.append('&');
                    }
                    catch (java.io.UnsupportedEncodingException ex) {}
                }
            }
        }
        HttpURLConnection httpConn = null;
        URL url = null;
        try {
            try {
                url = new URL(endpointUrl);
                httpConn = (HttpURLConnection)url.openConnection();
            }
            catch (MalformedURLException ex) {
                throw new Exception("endpointUrl is not valid.");
            }
            catch (IOException ex) {
                throw new Exception("HTTP error while opening the connection.");
            }
            catch (Exception ex) {
                throw new Exception("Undefined error while opening the HTTP connection.");
            }
            httpConn.setDoOutput(true); 
            httpConn.setUseCaches(false);
            httpConn.setDoInput(true);
            OutputStreamWriter writer = null;
            try {
                writer = new OutputStreamWriter(httpConn.getOutputStream());
                writer.write(parametersSB.toString());
                writer.flush();
            }
            catch (Exception ex) {
                throw new Exception("Could not get the Output Stream.");
            }
            InputStream inputStream = null;
            try {
                inputStream = httpConn.getInputStream();
            }
            catch (Exception ex){
                throw new Exception("Could not make the request to endpoint.");
            }
            BufferedReader br = new BufferedReader(new InputStreamReader(inputStream));
            String line = "";
            StringBuilder responseSB = new StringBuilder("");
            while ((line = br.readLine()) != null) {
                responseSB.append(line);
            }
            br.close();
            httpConn.disconnect();
            responseSB = new StringBuilder(responseSB.toString().trim());
            int responseLen = responseSB.length();
            if (responseLen > 0) {
                if (responseSB.charAt(0) == '[' && responseSB.charAt(responseLen - 1) == ']') {
                    responseSB.insert(0, "{\"d\": ");
                    responseSB.append(" }");
                }
                JSONParser jsonParser = new JSONParser();
                try {
                    responseJObj = (JSONObject)jsonParser.parse(responseSB.toString());
                }
                catch (ParseException ex) {
                    throw new Exception("Json response could not be parsed.");
                }
            }
        }
        catch (Exception ex) {
            throw new WebServiceException(
                String.format(
                    "Error calling Json Service [%s]. %s", 
                    endpointUrl,
                    ex.getMessage()
                )
            );
        }
        return responseJObj;
    }
    
    /**
     * Makes a call to WCF Json Service using HTTP POST method and returns the json object response.
     * @param endpointUrl Service endpoint URL.
     * @param parameters JSONObject to send as parameters.
     * @return A JSONObject with the response of the service.
     * @throws WebServiceException 
     */
    public static JSONObject callWcfJsonServiceWithPost(
            String endpointUrl,
            JSONObject parameters)
            throws WebServiceException {
        JSONObject responseJObj = null;
        if (endpointUrl == null) 
            throw new WebServiceException("endpointUrl cannot be null.");
        endpointUrl = endpointUrl.trim();
        if (parameters == null) 
            throw new WebServiceException("parameters cannot be null.");
        HttpURLConnection httpConn = null;
        URL url = null;
        try {
            try {
                url = new URL(endpointUrl);
                httpConn = (HttpURLConnection)url.openConnection();
            }
            catch (MalformedURLException ex) {
                throw new Exception("endpointUrl is not valid.");
            }
            catch (IOException ex) {
                throw new Exception("HTTP error while opening the connection.");
            }
            catch (Exception ex) {
                throw new Exception("Undefined error while opening the HTTP connection.");
            }
            httpConn.setDoOutput(true); 
            httpConn.setUseCaches(false);
            httpConn.setDoInput(true);
            httpConn.setRequestProperty("Content-Type", "application/json; charset=utf-8");
            OutputStreamWriter writer = null;
            try {
                writer = new OutputStreamWriter(httpConn.getOutputStream());
                writer.write(parameters.toJSONString());
                writer.flush();
            }
            catch (Exception ex) {
                throw new Exception("Could not get the Output Stream.");
            }
            InputStream inputStream = null;
            try {
                inputStream = httpConn.getInputStream();
            }
            catch (Exception ex){
                throw new Exception("Could not make the request to endpoint.");
            }
            BufferedReader br = new BufferedReader(new InputStreamReader(inputStream));
            String line = "";
            StringBuilder responseSB = new StringBuilder("");
            while ((line = br.readLine()) != null) {
                responseSB.append(line);
            }
            br.close();
            httpConn.disconnect();
            responseSB = new StringBuilder(responseSB.toString().trim());
            int responseLen = responseSB.length();
            if (responseLen > 0) {
                JSONParser jsonParser = new JSONParser();
                try {
                    responseJObj = (JSONObject)jsonParser.parse(responseSB.toString());
                }
                catch (ParseException ex) {
                    throw new Exception("Json response could not be parsed.");
                }
            }
        }
        catch (Exception ex) {
            throw new WebServiceException(
                String.format(
                    "Error calling Json Service [%s]. %s", 
                    endpointUrl,
                    ex.getMessage()
                )
            );
        }
        return responseJObj;
    }
}
