<template>
  <v-app>
    <v-app-bar app
               color="black"
               dense
               elevation="10"
               outlined
               rounded
               class="light-green--text text--accent-4"
    >
      <v-app-bar-nav-icon class="light-green--text text--accent-3"></v-app-bar-nav-icon>
      <v-toolbar-title>SYSTÈME DE SÉCURITÉ</v-toolbar-title>
      </v-app-bar>
    <v-content
    class="grey darken-4"
    >
      <v-container class="my-8">
        <v-layout row wrap>
          <v-flex xs12 md6 lg6 xl6 class="pa-4 ">
            <v-btn
                @click="ledOn"
                block
                color="light-green accent-3"
                elevation="3"
            >Allumer le Système de Sécurité</v-btn>
          </v-flex>
          <v-flex  xs12 md6  lg6 xl6 class="pa-4">
            <v-btn
                @click="ledOff"
                block
                color="light-green accent-3"
                elevation="3"
            >Éteindre le Système de Sécurité</v-btn>
          </v-flex>

        </v-layout>







      </v-container>

    </v-content>
  </v-app>
</template>

<script>
export default {
  name: "ControleLed",
  methods:{
    ledOn:function (){
      var json = {etat:true};
      fetch('http://10.0.0.21:8080/app/escapeGame/api/setEtatLed', {
        method: 'POST',
        headers: {'Content-Type': 'application/json'},
        body: JSON.stringify(json)
      }).then(res => {
        return res.text()}).then(data =>{
        alert(data);
    })
  },
  ledOff: function ()
  {
    var json = {etat:false};
    fetch('http://10.0.0.21:8080/app/escapeGame/api/setEtatLed', {
      method: 'POST',
      headers: {'Content-Type': 'application/json'},
      body: JSON.stringify(json)
    }).then(res => {
      return res.text()}).then(data =>{
      alert(data);
    })
  }


}
}
</script>

<style scoped>

</style>