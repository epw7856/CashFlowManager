# The Cash Flow Manager App is currently under construction! 
Check back frequently for updates.
- - - -

Cash Flow Manager
=========

The Cash Flow Manager desktop app is a complete personal expense, income, and investment manager built with C++14 in Qt. The app also provides mortgage, asset, and net worth tracking and analysis.


Table of contents
=================

<!--ts-->
   * [Cash Flow Manager](#cash-flow-manager)
   * [Table of contents](#table-of-contents)
   * [Installation](#installation)
   * [Usage](#usage)
      * [Budget Dashboard](#budget-dashboard)
      * [Monthly Budget Summary View](#monthly-budget-summary-view)
<!--te-->


Installation
============

Installation instructions coming soon!


Usage
=====


Budget Dashboard
-----

The Budget Dashboard provides an all-inclusive, simplified look at your financial health via two tabs: Monthly and Yearly Breakdown. 

<p align="center">
  <img src="/screenshots/Budget_Dashboard_Monthly_Breakdown.jpg" width="650" height="523"/><br>
  <i>Figure 1 - Budget Dashboard Monthly Breakdown Tab View</i>
</p>

The most despised yet critical aspect of personal finance is creating and tracking your month-to-month budget. After creating expense types and their associated monthly budget amounts, the Budget Dashboard updates automatically as transactions are added to show if you are on track. The *Expense Budget Status* bar chart is the best indicator of your spending habits for the month. Don't let the entire bar fill with red. Aim to keep as much of it green as possible by spending less than you make for the month and staying under-budget. The *Expense Budget* table gives you an in-depth categorized analysis of specifically where your hard earned dollars are going.

Similar to spending habits, you should also establish and track monthly investment targets. These types of investments are intended to be funded from gross income. This includes brokerage accounts and Traditional or Roth IRAs but not investments funded via employer-withheld salary contributions, such as a 401k account. But don't worry if you aren't ready to invest in anything yet. The Cash Flow Manager app will not show the status of investments unless you add them.

<p align="center">
  <img src="/screenshots/Budget_Dashboard_Yearly_Breakdown.jpg" width="650" height="523"/><br>
  <i>Figure 2 - Budget Dashboard Yearly Breakdown Tab View</i>
</p>

Both the monthly and yearly *Breakdown* tables give you a holistic view of your financial situation. It shows the following information:

* Expenses
* Investments
* Income
* Cash saved
* Budget surplus
* Savings ratio
* Additional principal paid, if a mortgage is configured 

The savings ratio is simply yearly expenses divided by yearly income multiplied by 100 to get a percentage. Budget surplus is the amount remaining in the budget for the month. The cash saved amount is the result of subtracting expenses and investments from income, which should be positive. A negative cash saved value is undesirable because it signifies that you are investing too much, spending too much, or both.

The *Income Distribution* pie chart within the Yearly Breakdown tab displays a different type of visualization of where your money is going. Just like with the *Expense Budget Status* bar chart, keep the red expense section as small as possible by spending less.


Monthly Budget Summary View
-----------

The Monthly Budget Summary shows categorized expenses and investments for each month of the current year. This dialog is beneficial because it allows you to see which expense categories 
were over-budget, or under-budget, throughout the year so that spending can be adjusted accordingly. Additionally, it shows investment amounts in relation to their defined targets. Any category amount that is over-budget or less than the investment target, is shaded in red. 
For each month, the view displays the final cash saved. As discussed previously, this value is what remains after subtracting expenses and investments from income for the month.

<p align="center">
  <img src="/screenshots/Monthly_Budget_Summary.jpg" width="750" height="571"/><br>
  <i>Figure 3 - Monthly Budget Summary View</i>
</p>
