This module provide a core of subsystem implementing ability to sell products for points.
 
Key points are:
 
 hook_reiscout_points_product_info()
 Declare the product and sell callback.
 
 reiscout_points_product_get_buy_form($product, $params)
 call it to get a form to buy your product and add it to page
 pass $params that would be passed to the sell callback.
 It will validate does user have enough points to buy the product and perform needed behaviour if not
 
 In your sell callback you do need only to implement the specific behaviour, e.g.
 you do not need to charge points.
  
 
 reiscout_points_product_decorate_form() 
 If you need to provide your own product purchase form implement a standard form function and wrap it with 
 reiscout_points_product_decorate_form().
 It actually do the job for reiscout_points_product_get_buy_form()
 If you use your custom form decorated with reiscout_points_product_decorate_form() you need to call reiscout_points_product_charge() in the form submit handler.