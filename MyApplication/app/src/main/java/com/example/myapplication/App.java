package com.example.myapplication;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Switch;
import android.widget.TextView;
import android.view.View;
import android.content.Intent;
import org.eclipse.paho.android.service.MqttAndroidClient;
import org.eclipse.paho.client.mqttv3.IMqttActionListener;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.IMqttToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;

import java.io.UnsupportedEncodingException;


public class App extends AppCompatActivity {
Button logout, control;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_app);
       logout=(Button) findViewById(R.id.button2);
       control=(Button)findViewById(R.id.button5);
        connect();

        control.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(App.this, Main2Activity.class);
                intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TASK | Intent.FLAG_ACTIVITY_NEW_TASK);
                startActivity(intent);
            }
        });
        logout.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(App.this, MainActivity.class);
                intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TASK | Intent.FLAG_ACTIVITY_NEW_TASK);
                startActivity(intent);
            }
        });

    }

    public void connect(){

        String clientId = MqttClient.generateClientId();
        final MqttAndroidClient client =
                new MqttAndroidClient(this.getApplicationContext(), "tcp://m16.cloudmqtt.com:13330",
                        clientId);

        MqttConnectOptions options = new MqttConnectOptions();
        options.setMqttVersion(MqttConnectOptions.MQTT_VERSION_3_1);
        options.setCleanSession(false);
        options.setUserName("yrzmecpp");
        options.setPassword("5UbSz2Rz4gVk".toCharArray());
        try {
            IMqttToken token = client.connect(options);
            //IMqttToken token = client.connect();
            token.setActionCallback(new IMqttActionListener() {
                @Override
                public void onSuccess(IMqttToken asyncActionToken) {
                    // We are connected
                    Log.d("file", "onSuccess");
                    //publish(client,"payloadd");
                    subscribe(client,"Soil Moisture");
                    subscribe(client,"Light Intensity");
                    subscribe(client,"Temperature(soil)");
                    subscribe(client,"Light State");
                    subscribe(client,"Pump State");
                    subscribe(client,"Temperature(air)");
                    subscribe(client,"Humidity");
                    subscribe(client,"PH Value");
                    client.setCallback(new MqttCallback() {
                        EditText tt = (EditText) findViewById(R.id.editText10);
                        EditText th = (EditText) findViewById(R.id.editText14);
                        EditText ti = (EditText) findViewById(R.id.editText12);
                        EditText a=(EditText)findViewById(R.id.editText15);
                        EditText b=(EditText)findViewById(R.id.editText16);
                        EditText c=(EditText)findViewById(R.id.editText11);
                        EditText d=(EditText)findViewById(R.id.editText13);
                        EditText e=(EditText)findViewById(R.id.editText9);
                        @Override
                        public void connectionLost(Throwable cause) {

                        }
                        @Override
                        public void messageArrived(String topic, MqttMessage message) throws Exception {
                            Log.d("file", message.toString());

                            if (topic.equals("Soil Moisture")){
                                tt.setText(message.toString());
                            }

                            if (topic.equals("Light Intensity")){
                                ti.setText(message.toString());
                            }

                            if (topic.equals("Temperature(soil)")){
                                th.setText(message.toString());
                            }

                            if (topic.equals("Light State")){
                                b.setText(message.toString());
                            }


                            if (topic.equals("Pump State")){
                                a.setText(message.toString());
                            }

                            if (topic.equals("Temperature(air)")){
                                c.setText(message.toString());
                            }
                            if (topic.equals("PH Value")){
                                d.setText(message.toString());
                            }
                            if (topic.equals("Humidity")){
                                e.setText(message.toString());
                            }


                        }
                        @Override
                        public void deliveryComplete(IMqttDeliveryToken token) {

                        }
                    });
                }

                @Override
                public void onFailure(IMqttToken asyncActionToken, Throwable exception) {
                    // Something went wrong e.g. connection timeout or firewall problems
                    Log.d("file", "onFailure");

                }
            });
        } catch (MqttException e) {
            e.printStackTrace();
        }
    }


    public void publish(MqttAndroidClient client, String payload)
    {
        String topic = "foo/bar";
        byte[] encodedPayload = new byte[0];
        try {
            encodedPayload = payload.getBytes("UTF-8");
            MqttMessage message = new MqttMessage(encodedPayload);
            client.publish(topic, message);
        } catch (UnsupportedEncodingException | MqttException e) {
            e.printStackTrace();
        }
    }


    public void subscribe(MqttAndroidClient client , String topic)
    {
        int qos = 1;
        try {
            IMqttToken subToken = client.subscribe(topic, qos);
            subToken.setActionCallback(new IMqttActionListener() {

                @Override
                public void onSuccess(IMqttToken asyncActionToken) {
                    // The message was published
                }

                @Override
                public void onFailure(IMqttToken asyncActionToken,
                                      Throwable exception) {
                    // The subscription could not be performed, maybe the user was not
                    // authorized to subscribe on the specified topic e.g. using wildcards
                }
            });
        } catch (MqttException e) {
            e.printStackTrace();
        }
    }


}
