<template>
  <v-app>
    <v-app-bar app
               color="black"
               dense
               elevation="10"
               outlined
               rounded
    >
      <v-app-bar-nav-icon class="light-green--text text--accent-3"></v-app-bar-nav-icon>
      <v-toolbar-title
          class="light-green--text text--accent-3"
      >HackerStation</v-toolbar-title>
    </v-app-bar>
    <v-content
    class="grey darken-4">
      <v-container class="my-8">
        <v-form>
        <v-layout column wrap justify-start align-start>
          <v-flex xs12 md3 lg3 xl3 >
             <v-text-field label="Username"
             dark
             v-model="username"
             class="white--text"
             color="light-green accent-3"
             outlined>
             </v-text-field>
          </v-flex>
          <v-flex  xs12 md3  lg3 xl3>
              <v-text-field
                  v-model="password"
                  dark
                  label="Password"
                  type="password"
                  color="light-green accent-3 white--text"
                  outlined>
              </v-text-field>
          </v-flex>
          <v-flex>
              <v-btn
                  @click="login"
                  color="light-green accent-3"
                  elevation="3"
              >Sudmit</v-btn>
          </v-flex>

        </v-layout>
        </v-form>
      </v-container>

    </v-content>
  </v-app>



</template>

<script>
export default {
  name: "loginPage",
  data(){
    return {
      username:"",
      password:""
    }
  },
  methods: {
    login:function ()
    {
      var json = {"username": this.username,"password": this.password};
      fetch('http://10.0.0.21:8080/app/escapeGame/api/login', {
        method: 'POST',
        headers: {'Content-Type': 'application/json'},
        body: JSON.stringify(json)
      }).then(res => {
        return res.json()}).then(data =>{
          if(data["login"] == true)
          {
            this.$router.push("controlled")
          }else{
            alert("Username ou Password invalide");
          }

      })
    }
  },
}
</script>

<style scoped>

</style>