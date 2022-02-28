package com.example.victoria.generarrutagps;

import android.graphics.Color;
import android.os.AsyncTask;
import android.support.v4.app.FragmentActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;

import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.BitmapDescriptorFactory;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;
import com.google.android.gms.maps.model.PolylineOptions;

import org.json.JSONObject;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class MapsActivity extends FragmentActivity implements OnMapReadyCallback {

    private GoogleMap mMap;
    String URL;

    LatLng PalacioGobierno;
    LatLng CasadelGober;
    LatLng UniversidadPatito;
    LatLng Intermedio1;
    LatLng Intermedio2;

    LatLng Inicial; // Casa del JEFE
    LatLng Final; // Univ. Patito
    LatLng EstadioCorre; // El Corre
    LatLng UPVictoria; // Alma Máter

    static String LlaveProyecto = "AIzaSyCeThucUanCALfMUYskFazmlAD8eoqRHJo";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_maps);
        // Obtain the SupportMapFragment and get notified when the map is ready to be used.
        SupportMapFragment mapFragment = (SupportMapFragment) getSupportFragmentManager().findFragmentById(R.id.map);
        mapFragment.getMapAsync(this);

        // Crear Coordenadas (o traerlas de alguna parte)
        PalacioGobierno = new LatLng(23.73069861381223, -99.1513055562973); // Palacio de Gobierno
        CasadelGober = new LatLng(23.76282137431006, -99.13967683911324); // Casa del JEFE
        UniversidadPatito = new LatLng(23.716054, -99.152513); // Univ. Patito
        EstadioCorre = new LatLng(23.739253, -99.1525); // El Corre
        UPVictoria = new LatLng(23.7283452, -99.0737071); // UPVIC

        Intermedio1 = CasadelGober;
        Intermedio2 = UPVictoria;
        Final = UniversidadPatito;
        Inicial = EstadioCorre;

        URL = getMapsApiDirectionsUrl();
        Toast.makeText(getApplicationContext(),URL,Toast.LENGTH_SHORT).show();

        ReadTask downloadTask = new ReadTask();
        downloadTask.execute(URL);
    }


    /**
     * Manipulates the map once available.
     * This callback is triggered when the map is ready to be used.
     * This is where we can add markers or lines, add listeners or move the camera. In this case,
     * we just add a marker near Sydney, Australia.
     * If Google Play services is not installed on the device, the user will be prompted to install
     * it inside the SupportMapFragment. This method will only be triggered once the user has
     * installed Google Play services and returned to the app.
     */
    @Override
    public void onMapReady(GoogleMap googleMap) {
        mMap = googleMap;

        // Add a marker in Sydney and move the camera
        /*LatLng sydney = new LatLng(-34, 151);
        mMap.addMarker(new MarkerOptions().position(sydney).title("Marker in Sydney"));
        mMap.moveCamera(CameraUpdateFactory.newLatLng(sydney));*/

        /*LatLng sydney = Inicial;
        mMap.addMarker(new MarkerOptions().position(sydney).title("Marker in Sydney"));
        mMap.moveCamera(CameraUpdateFactory.newLatLng(sydney));*/

        // Ponerlo Marcadores de COLORES
        mMap.addMarker(new MarkerOptions().position(Inicial).title("Inicio").icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_MAGENTA)));
        mMap.addMarker(new MarkerOptions().position(Final).title("Final").icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_CYAN)));
        mMap.addMarker(new MarkerOptions().position(Intermedio1).title("Intermedio1").icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_GREEN)));
        mMap.addMarker(new MarkerOptions().position(Intermedio2).title("UPV").icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_RED)));
        mMap.addMarker(new MarkerOptions().position(PalacioGobierno).title("PalacioGobierto").icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_ORANGE)));

        // Hacer el ZOOM sobre el punto de inicio
        mMap.animateCamera(CameraUpdateFactory.newLatLngZoom(Inicial, 16));


    }

    private String getMapsApiDirectionsUrl() {
        // Con dos puntos intermedios (Podrian ser N)

        //String url = "https://maps.googleapis.com/maps/api/directions/json?origin=Toronto&destination=Montreal&key="+LlaveProyecto;

        String url = "https://maps.googleapis.com/maps/api/directions/json?origin="
                +Inicial.latitude+","+Inicial.longitude+"&destination="+
                Final.latitude+","+Final.longitude+
                "&waypoints=optimize:true|"+
                Intermedio1.latitude+","+Intermedio1.longitude+"|"+"" +
                Intermedio2.latitude+","+Intermedio2.longitude +
                "&key="+LlaveProyecto;
        return url;
    }

    private class ReadTask extends AsyncTask<String, Void, String> {
        @Override
        protected String doInBackground(String... url) {
            String data = "";
            try {
                HttpConnection http = new HttpConnection();
                data = http.readUrl(url[0]);
            } catch (Exception e) {
                Log.d("Background Task", e.toString());
            }
            return data;
        }

        @Override
        protected void onPostExecute(String result) {
            super.onPostExecute(result);
            // Toast.makeText(mContext, "" + result, Toast.LENGTH_LONG).show();
            new ParserTask().execute(result);
        }
    }

    private class ParserTask extends
            AsyncTask<String, Integer, List<List<HashMap<String, String>>>> {

        @Override
        protected List<List<HashMap<String, String>>> doInBackground(
                String... jsonData) {

            JSONObject jObject;
            List<List<HashMap<String, String>>> routes = null;

            try {
                jObject = new JSONObject(jsonData[0]);
                PathJSONParser parser = new PathJSONParser();
                routes = parser.parse(jObject);
            } catch (Exception e) {
                e.printStackTrace();
            }
            return routes;
        }

        @Override
        protected void onPostExecute(List<List<HashMap<String, String>>> routes) {
            ArrayList<LatLng> points = null;
            PolylineOptions polyLineOptions = null;

            if (routes.size()>0) {

                // traversing through routes
                for (int i = 0; i < routes.size(); i++) {
                    points = new ArrayList<LatLng>();
                    polyLineOptions = new PolylineOptions();
                    List<HashMap<String, String>> path = routes.get(i);

                    for (int j = 0; j < path.size(); j++) {
                        HashMap<String, String> point = path.get(j);

                        double lat = Double.parseDouble(point.get("lat"));
                        double lng = Double.parseDouble(point.get("lng"));
                        LatLng position = new LatLng(lat, lng);

                        points.add(position);
                    }

                    polyLineOptions.addAll(points);
                    polyLineOptions.width(2);
                    polyLineOptions.color(Color.BLUE);
                }

                mMap.addPolyline(polyLineOptions);
            } else
                Toast.makeText(getApplicationContext(), "NO HAY DATOS DE LA RUTA", Toast.LENGTH_SHORT).show();

        }
    }
}
