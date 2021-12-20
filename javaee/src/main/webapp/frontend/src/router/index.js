import Vue from 'vue'
import VueRouter from 'vue-router'
import ControleLed from "@/components/ControleLed";
import loginPage from "@/components/loginPage";
Vue.use(VueRouter)

const routes = [
  {
    path: '/',
    name: 'loginPage',
    component: loginPage
  },
  {
    path: '/controlLed',
    name: 'ControleLed',
    component: ControleLed
  },
]

const router = new VueRouter({
  mode: "hash",
  base:"/app/",
  routes
})

export default router
