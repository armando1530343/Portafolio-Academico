package com.example.victoria.visor_video;

import android.content.Intent;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.media.MediaPlayer;
import android.net.Uri;
import android.os.Build;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.webkit.URLUtil;
import android.widget.Button;
import android.widget.EditText;
import android.widget.MediaController;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.VideoView;

public class MainActivity extends AppCompatActivity {

    Button examinar, play;
    EditText url;
    private final int PICKER = 1;
    VideoView reproductor;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        examinar = (Button)findViewById(R.id.examinar);
        url = (EditText)findViewById(R.id.url);
        play = (Button)findViewById(R.id.play);
        reproductor = (VideoView)findViewById(R.id.video);

        reproductor.setMediaController(new MediaController(this));

        examinar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
                intent.setType("file/*");
                intent.addCategory(intent.CATEGORY_OPENABLE);

                try{
                    startActivityForResult(
                            Intent.createChooser(intent, "Selecciona un video de la galeria"),
                            PICKER
                    );
                }
                catch (Exception e){
                    Toast.makeText(MainActivity.this, e.getMessage(), Toast.LENGTH_LONG).show();
                }
            }
        });
        play.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                try {
                    //String file = "android.resource://"+getPackageName()+"/"+R.raw.dbz_rap;//url.getText().toString();
                    String file = url.getText().toString();
                    reproductor.setVideoURI(Uri.parse(file));
                    reproductor.start();
                    /*reproductor.setVideoPath(file);
                    reproductor.requestFocus();
                    reproductor.start();*/


                }
                catch (Exception e){
                    Toast.makeText(MainActivity.this, e.getMessage(), Toast.LENGTH_LONG).show();
                }

            }
        });

    }
    protected void onActivityResult(int requestCode, int resultCode, Intent data){
        switch (requestCode){
            case PICKER:
                if(resultCode == RESULT_OK){
                    String filePath = data.getData().getPath();
                    url.setText(filePath);
                }
                break;
        }
    }
}
