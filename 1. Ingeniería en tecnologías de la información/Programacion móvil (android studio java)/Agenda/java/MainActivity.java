package com.example.armando.agenda;
/*
Fuente con ligeras modificaciones:
http://android-er.blogspot.mx/2013/06/start-activity-once-notification-clicked.html
 */


import java.util.Calendar;

import android.app.DatePickerDialog;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.TimePickerDialog;
import android.app.AlarmManager;
import android.content.BroadcastReceiver;
import android.content.Intent;
import android.os.Bundle;
import android.app.Activity;
import android.os.CountDownTimer;
import android.support.v4.app.NotificationCompat;
import android.view.View;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.TimePicker;
import android.widget.Toast;

import android.content.Context;

public class MainActivity extends Activity{

	EditText evento_txt, fecha_txt, hora_txt;
	Button btn;
	private int dia_actual, mes_actual, anio_actual, hora_actual, minuto_actual;
	private int dia, mes, anio, hora, minuto;

	int limite=0, intervalo=1000;

	MyCount counter;
    int NumeroLectura;

	NotificationCompat.Builder notificacion;
	private static final int ID = 0;
	

	@Override
	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		//counter = new MyCount(5000,1000);
		Calendar now = Calendar.getInstance();

		NumeroLectura=0;

		btn = (Button)findViewById(R.id.btn);
		btn.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View view) {
				// Original ...
				if(evento_txt.getText().length() == 0 && fecha_txt.getText().length() == 0 && hora_txt.getText().length() == 0){
					Toast.makeText(MainActivity.this, "Hay campos vacios", Toast.LENGTH_SHORT).show();
					return;
				}
				if(anio < anio_actual && mes < mes_actual && dia < dia_actual && hora < hora_actual && minuto <= minuto_actual){
					Toast.makeText(MainActivity.this, "Se ingreso una hora anterior", Toast.LENGTH_SHORT).show();
					return;
				}

				int a=anio_actual,
						m=mes_actual,
						d=dia_actual,
						h=hora_actual,
						min=minuto_actual;
				do {

					min++;
					if(min >= 60) {
						min = 0;
						hora++;
					}
					if(hora >= 24){
						hora = 0;
						dia++;
					}
					if(dia >= 30){
						dia = 1;
						mes++;
					}
					if(mes > 12){
						mes = 1;
						anio++;
					}

					limite+=60000;


				}while(a < anio && m < mes && d < dia && h < hora && min < minuto);

				counter = new MyCount(limite,1000);
				/*Calendar now = Calendar.getInstance();
				Calendar tmp = (Calendar) now.clone();
				Calendar tmp2 = (Calendar) now.clone();
				Calendar tmp3 = (Calendar) now.clone();
				Calendar tmp4 = (Calendar) now.clone();
				tmp.add(Calendar.SECOND, 30);
				tmp2.add(Calendar.MINUTE, 1);
				tmp3.add(Calendar.MINUTE, 2);
				tmp4.add(Calendar.MINUTE, 3);
				/*setAlarm(tmp,  1001);
				setAlarm(tmp2, 1002);
				setAlarm(tmp3, 1003);
				setAlarm(tmp4, 1004);*/

				// Adaptandole el Counter Visto en Clase para que cada determinado tiempo arroje una Notificación...
				counter.start();
			}
		});


		notificacion = new NotificationCompat.Builder(this);
		notificacion.setAutoCancel(true);

		evento_txt = (EditText)findViewById(R.id.evento);
		fecha_txt = (EditText)findViewById(R.id.fecha);
		hora_txt = (EditText)findViewById(R.id.hora);
	}

	private void setAlarm(Calendar targetCal, int R){

		//info.append("\n" + "Fecha y Hora de Envio de Notificación:  " + targetCal.getTime() + "***");

		Intent intent = new Intent(getBaseContext(), AlarmReceiver.class);
		intent.putExtra("R",R);
		intent.putExtra("E1",evento_txt.getText().toString());
		PendingIntent pendingIntent = PendingIntent.getBroadcast(getBaseContext(), R, intent, 0);
		AlarmManager alarmManager = (AlarmManager)getSystemService(Context.ALARM_SERVICE);
		alarmManager.set(AlarmManager.RTC_WAKEUP, targetCal.getTimeInMillis(), pendingIntent);


	}

	//countdowntimer is an abstract class, so extend it and fill in methods
	public class MyCount extends CountDownTimer{

		public MyCount(long millisInFuture, long countDownInterval) {
			super(millisInFuture, countDownInterval);
		}

		@Override
		public void onFinish() {
			//tv.setText(”done!”);
			Calendar now = Calendar.getInstance();
			Calendar tmp = (Calendar) now.clone();
			tmp.add(Calendar.SECOND, 1);
			setAlarm(tmp, NumeroLectura);
			NumeroLectura++;
			//this.start(); // Volver a Iniciar
		}

		@Override
		public void onTick(long millisUntilFinished) {
			//tv.setText(”Left: ” + millisUntilFinished/1000);

		}

	}

	public void clic_fecha(View v){
		final Calendar c = Calendar.getInstance();
		dia_actual = c.get(Calendar.DAY_OF_MONTH);
		mes_actual = c.get(Calendar.MONTH);
		anio_actual = c.get(Calendar.YEAR);

		DatePickerDialog datePickerDialog = new DatePickerDialog(this, new DatePickerDialog.OnDateSetListener() {
			@Override
			public void onDateSet(DatePicker datePicker, int i, int i1, int i2) {
				fecha_txt.setText(i2 + "/" + (i1+1) + "/" + i);
				dia = i; mes = i1; anio = i2;
			}

		}, dia_actual, mes_actual, anio_actual);

		datePickerDialog.show();
	}
	public void clic_hora(View v){
		final Calendar c = Calendar.getInstance();
		hora_actual = c.get(Calendar.HOUR_OF_DAY);
		minuto_actual = c.get(Calendar.MINUTE);

		TimePickerDialog timePickerDialog = new TimePickerDialog(this, new TimePickerDialog.OnTimeSetListener() {
			@Override
			public void onTimeSet(TimePicker timePicker, int i, int i1) {
				hora_txt.setText(i + ":" + i1);
				hora = i; minuto = i1;
			}
		}, hora_actual, minuto_actual, false);

		timePickerDialog.show();
	}





}
