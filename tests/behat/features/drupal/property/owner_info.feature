Feature: Check owner info buttons appearance.
  Scenario: Do I see button to buy points if there is no points and no filled owner info.
    Given I logged in as 'picture_buyer'
    # Go to purchased node
    Given I go to "property/472" page
    # The node is purchased so address visible
    Given I should see "Address"
    # Owner address not filled it
    Given I should not see "Owner Address"
    # User have no points to get owner info
    Given I have no get_owner_info points
    Given I go to "/user/3/points" page
    And I see "No Points earned"
    Then I go to "property/472" page
    And I should see "Buy Abitity to Get Owner Info"

  Scenario: Do I see button to get owner info after I purchase the points.
    Given I logged in as 'picture_buyer'
    # Go to purchased node
    Given I go to "property/472" page
    # The node is purchased so address visible
    Given I should see "Address"
    # Owner address not filled it
    Given I should not see "Owner Address"
    # User have no points to get owner info
    Given I see "Buy Abitity to Get Owner Info"
    Then I press "Buy Abitity to Get Owner Info"
    And I should see "Buy 10 points for Owner Info request added to your cart."
    Then I go to "/cart" page
    And I press "Checkout"
    Then I should see "Checkout"
    And I fill in billing info fields
    And I press "Continue to next step"
    Then I should see "Review Order"
    And I fill "Card owner" with "John Dow"
    And I fill "Card Number" with "4111 1111 1111 1111"
    And I fill "Expiration" with "05 / 19"
    And I fill "Security code" with "333"
    Then I press "Continue to next step"
    And I should see "Checkout complete"
    # After the points purchased I should see Get Owner Info button
    Given I go to "user/3/points" page
    # I should see that I have the points on points tab on account page.
    Then I should see "Payed points (owner info)"
    Given I go to "property/472" page
    Then I should see "Get Property Owner (10 points left)"

  Scenario: Node filled with owner info after clicking the Get Property Owner button.
    Given I go to "property/472" page
    Given I should see "Address"
    # Owner address not filled it
    Given I should not see "Owner Address"
    Given I should see "Get Property Owner (10 points left)"
    Then I press "Get Property Owner"
    AND I SEE ACCESS DENIED